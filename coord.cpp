#include "coord.h"

bool get_baricentic_coord(int x, int y, std::vector<nc::NdArray<float>> & tr_f, float* lambda, bool is_check_equlation) {
	//tr_f - triangle float vertexes
	// lambda size is 3.
	//lambda0 = ((x1 -x2)*(y-y2) -(y1 -y2)*(x-x2)) / ((x1 -x2)*(y0 -y2) -(y1 -y2) *(x0 -x2));
	//lambda1 = ((x2 -x0)*(y -y0) -(y2 -y0)*(x -x0)) / ((x2 -x0)*(y1 -y0) -(y2 -y0)* (x1 -x0));
	//lambda2 = ((x0 -x1)*(y -y1) -(y0 -y1)*(x -x1)) / ((x0 -x1)*(y2 -y1) -(y0 -y1)* (x2 -x1));
	// x0 - tr_f[0](0,0), y0 - tr_f[0](0,1)
	// x1 - tr_f[1](0,0), y1 - tr_f[1](0,1)
	// x2 - tr_f[2](0,0), y2 - tr_f[2](0,1)
	float lambda0 = ((tr_f[1](0, 0) - tr_f[2](0, 0))*(y - tr_f[2](0, 1)) - (tr_f[1](0, 1) - tr_f[2](0, 1))*(x - tr_f[2](0, 0))) /
		((tr_f[1](0, 0) - tr_f[2](0, 0))*(tr_f[0](0, 1) - tr_f[2](0, 1)) - (tr_f[1](0, 1) - tr_f[2](0, 1))* (tr_f[0](0, 0) - tr_f[2](0, 0)));
	if (lambda0 < 0)
		return false;
	float lambda1 = ((tr_f[2](0, 0) - tr_f[0](0, 0))*(y - tr_f[0](0, 1)) - (tr_f[2](0, 1) - tr_f[0](0, 1))*(x - tr_f[0](0, 0))) /
		((tr_f[2](0, 0) - tr_f[0](0, 0))*(tr_f[1](0, 1) - tr_f[0](0, 1)) - (tr_f[2](0, 1) - tr_f[0](0, 1))* (tr_f[1](0, 0) - tr_f[0](0, 0)));
	if (lambda1 < 0)
		return false;
	float lambda2 = ((tr_f[0](0, 0) - tr_f[1](0, 0))*(y - tr_f[1](0, 1)) - (tr_f[0](0, 1) - tr_f[1](0, 1))*(x - tr_f[1](0, 0))) /
		((tr_f[0](0, 0) - tr_f[1](0, 0))*(tr_f[2](0, 1) - tr_f[1](0, 1)) - (tr_f[0](0, 1) - tr_f[1](0, 1))* (tr_f[2](0, 0) - tr_f[1](0, 0)));
	if (lambda2 < 0)
		return false;
	lambda[0] = lambda0;
	lambda[1] = lambda1;
	lambda[2] = lambda2;
	if (is_check_equlation)
		std::cout << lambda0 + lambda1 + lambda2 << '\n';
	return true;
}

std::vector<std::vector<int>> get_borders_triangle(std::vector<nc::NdArray<int>> & tr_i) {
	//tr_f - triangle integer vertexes
	std::vector<std::vector<int>> ans{
		{1000000, -1},
		{1000000, -1}
	};
	//цикл по точкам
	for (int i = 0; i < 3; ++i) {
		// x and y цикл
		for (int j = 0; j < 2; ++j) {
			//min если текущий минимум для текущего номера координаты меньше значения текущего номера координаты
			if (ans[j][0] > tr_i[i](0, j)) {
				ans[j][0] = tr_i[i](0, j);
			}
			//max
			if (ans[j][1] < tr_i[i](0, j)) {
				ans[j][1] = tr_i[i](0, j);
			}
		}
	}
	return ans;
}
