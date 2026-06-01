#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
using namespace std;

#define HEADER_SIZE 54

int main(void)
{
	const char* image_file = "../lab15/sample.bmp";
	const char* out_file = "../lab15/image_edited.bmp";

	ifstream img_in(image_file, ios::binary);
	if (! img_in.is_open()) {
		cout << "Ошибка при открытии файла: " << image_file << "\n";
		return 1;
	}

	char header[HEADER_SIZE];
	img_in.read(header, HEADER_SIZE);

	cout << "Header:\n";
	for (int i = 0; i < HEADER_SIZE*2; i++)
		cout << header[i] << " : ";
	cout << "\n";

	int width_px = *(int*)&header[18];
	int height_px = *(int*)&header[22];

	cout << "Dimentions: " << width_px << "x" << height_px << "\n";

	// 24 бит на пиксель, B8 G8 R8

	char pixel_arr[height_px][width_px][3]; // [столбцы][строки][bgr]

	for (int i = 0; i < height_px; i++) {
		for (int j = 0; j < width_px; j++)
			img_in.read(pixel_arr[i][j], 3);
	}

	img_in.close();

	int x1, y1, x2, y2;
	float mod_r, mod_g, mod_b;

	cout << "Введите координаты x1, y1 (левый верхний угол), x2, y2 (правый нижнй) (>=1),\n";
	cout << "модификаторы цвета R, G, B (0-255)\n";
	cout << "(Декартова система координат)\n> ";
	cin >> x1 >> y1 >> x2 >> y2 >> mod_r >> mod_g >> mod_b;
	cout << "\n";
	//x1 = 50; y1 = 300; x2 = 300; y2 = 50;
	//cin >> mod_r >> mod_g >> mod_b;
	x1 -= 1;
	x2 -= 1;
	y1 -= 1;
	y2 -= 1;

	for (int h = 0; h < height_px; h++) {
		for (int w = 0; w < width_px; w++) {
			if (h >= y2 && h <= y1) {
				if (w >= x1 && w <= x2) {
					int pr = (unsigned char)pixel_arr[h][w][2];
					int pg = (unsigned char)pixel_arr[h][w][1];
					int pb = (unsigned char)pixel_arr[h][w][0];

					if (pr == 0 && (mod_r != 1))
						pr = 1;
					int r_clamped = pr * mod_r;
					if (r_clamped > 255)
						r_clamped = 255;

					if (pg == 0 && (mod_g != 1))
						pg = 1;
					int g_clamped = pg * mod_g;
					if (g_clamped > 255)
						g_clamped = 255;

					if (pb == 0 && (mod_b != 1))
						pb = 1;
					int b_clamped = pb * mod_b;
					if (b_clamped > 255)
						b_clamped = 255;

					pixel_arr[h][w][2] = r_clamped;
					pixel_arr[h][w][1] = g_clamped;
					pixel_arr[h][w][0] = b_clamped;
				}
			}
		}
	}


	
	//system("[ -f ../lab15/image_edited.bmp ] && rm ../lab15/image_edited.bmp");
	ofstream img_out(out_file, ios::binary);
	if (! img_out.is_open()) {
		cout << "Ошибка при открытии файла: " << out_file << "\n";
		return 1;
	}

	img_out.write(header, HEADER_SIZE);
	img_out.close();

	ofstream img_out_data(out_file, ios::app);
	if (! img_out_data.is_open()) {
		cout << "Ошибка при открытии файла: " << out_file << "\n";
		return 1;
	}

	for (int i = 0; i < height_px; i++){
		for (int k = 0; k < width_px; k++) {
			for (int l = 0; l < 3; l++)
				img_out_data << pixel_arr[i][k][l];
		}
	}
	cout << "Готово.\n";

	img_out_data.close();

	return 0;
}


