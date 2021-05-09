#include "ObjParser.h"


ObjParser::ObjParser(std::string file_path) :file_p(file_path) {
	this->parse_file(false);
}
ObjParser::ObjParser(std::string file_path, bool is_test) : file_p(file_path) {
	this->parse_file(is_test);
};

void ObjParser::parse_file(bool is_test) {
	std::ifstream in;
	in.open(this->file_p, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << this->file_p << std::endl;
		exit(1);
	}
	std::string line;
	std::vector<std::vector<float>> vertexes, normals, textures;
	/*{vertex {{0},{1},{2}},texture {{0},{1},{2}},normals {{0},{1},{2}} }*/

	std::vector<std::vector<int>> fvertex{ std::vector<int>(),std::vector<int>(),std::vector<int>() };
	std::vector<std::vector<int>> ftexture{ std::vector<int>(),std::vector<int>(),std::vector<int>() };
	std::vector<std::vector<int>> fnormal{ std::vector<int>(),std::vector<int>(),std::vector<int>() };

	int i_f = 0, i_v = 0, i_n = 0, i_t = 0; // for testing

	while (getline(in, line)) {
		std::string to_switch = line.substr(0, 2); // substing from 0 with lenght 2

		// vertex values
		if (to_switch == std::string("v ")) {
			std::istringstream iss(line.substr(2));
			float x, y, z;
			iss >> x >> y >> z;
			vertexes.push_back({ x, y, z }); // push back vector
			//test[
			if (is_test) {
				if (i_v < 2)
					std::cout << "vertexes\n" << x << ' ' << y << ' ' << z << std::endl;
				++i_v;
			}
			//test]
		}
		// vertex normals
		if (to_switch == std::string("vn")) {
			std::istringstream iss(line.substr(3));
			float n1, n2, n3;
			iss >> n1 >> n2 >> n3;
			normals.push_back({ n1, n2, n3 }); // push back vector
			//test[
			if (is_test) {
				if (i_n < 2)
					std::cout << "normals\n" << n1 << ' ' << n2 << ' ' << n3 << std::endl;
				++i_n;
			}
			//test]
		}
		// vertex texture
		if (to_switch == std::string("vt")) {
			std::istringstream iss(line.substr(3));
			float x, y;
			iss >> x >> y;
			textures.push_back({ x, y }); // push back vector
			//test[
			if (is_test) {
				if (i_t < 2)
					std::cout << "textures\n" << x << ' ' << y << std::endl;
				++i_t;
			}
			//test]
		}
		// triangles
		if (to_switch == std::string("f ")) {
			std::istringstream iss(line.substr(2));
			int v1, v2, v3, t1, t2, t3, n1, n2, n3;
			char temp;
			iss >> v1 >> temp >> t1 >> temp >> n1 >> v2 >> temp >> t2 >> temp >> n2 >> v3 >> temp >> t3 >> temp >> n3;
			//test[
			if (is_test) {
				if (i_f < 2)
					std::cout << v1 << temp << t1 << temp << n1 << ' ' << v2 << temp << t2 << temp << n2 << ' ' << v3 << temp << t3 << temp << n3 << std::endl;
				++i_f;
			}
			//test]
			// push back values
			//Нумерация вершин с 1
			fvertex[0].push_back(v1 - 1);
			fvertex[1].push_back(v2 - 1);
			fvertex[2].push_back(v3 - 1);

			fnormal[0].push_back(n1 - 1);
			fnormal[1].push_back(n2 - 1);
			fnormal[2].push_back(n3 - 1);

			ftexture[0].push_back(t1 - 1);
			ftexture[1].push_back(t2 - 1);
			ftexture[2].push_back(t3 - 1);
		}
	}
	if (is_test) {
		std::cout << std::endl << "DATA IN VECTOR\n";
		std::cout << "vertex  : " << vertexes.size() << ' ' << vertexes[1].size() << ' ' << vertexes[2].size() << '\n';
		std::cout << "normals : " << normals.size() << ' ' << normals[1].size() << ' ' << normals[2].size() << '\n';
		std::cout << "textures: " << textures.size() << ' ' << textures[1].size() << ' ' << textures[2].size() << '\n';

		std::cout << "fvertex  : " << fvertex.size() << ' ' << fvertex[0].size() << "( " << fvertex[0][0]<< " )" << fvertex[1].size() << "( " << fvertex[1][0]<< " )" << fvertex[2].size() << "( " << fvertex[2][0]<< " )\n";
		std::cout << "fnormals : " << fnormal.size() << ' ' << fnormal[0].size() << "( "<< fnormal[0][0]  << " )" << fnormal[1].size() << "( "<< fnormal[1][0] << " )" << fnormal[2].size() << "( " << fnormal[2][0]<< " )\n";
		std::cout << "ftextures: " << ftexture.size() << ' ' << ftexture[0].size() << "( " << ftexture[0][0]<< " )" << ftexture[1].size() << "( " << ftexture[1][0]<< " )" << ftexture[2].size() << "( " << ftexture[2][0]<< " )\n";
		std::cout << std::endl;
	}
	this->normals = nc::asarray<float>(normals);
	this->vertexes = nc::asarray<float>(vertexes);
	this->textures = nc::asarray<float>(textures);

	this->tri_ind[VERTEX] = nc::asarray<int>(fvertex);
	this->tri_ind[NORMAL] = nc::asarray<int>(fnormal);
	this->tri_ind[TEXTURE] = nc::asarray<int>(ftexture);

	if (is_test) {
		std::cout << std::endl << "DATA IN NDARRAY\n";
		std::cout << "vertex shape : "; this->vertexes.shape().print();
		std::cout << "texture shape: "; this->textures.shape().print();
		std::cout << "normals shape: "; this->normals.shape().print();

		std::cout << "vertexs index shape : "; this->tri_ind[VERTEX].shape().print();
		std::cout << "textures index shape: "; this->tri_ind[TEXTURE].shape().print();
		std::cout << "normals index shape : "; this->tri_ind[NORMAL].shape().print();
		std::cout << "\n\n\n";
	}
}
//void ObjParser::handle_copy_in_ndarray(std::vector<float> from, nc::NdArray<float> in) {
//
//};
