#include<iostream>
#include"Game.hpp"
#include"GSnake.hpp"

using std::cin;
using std::cout;
using std::endl;

cv::Mat home;
bool tips = true;
void mouse(int event, int x, int y, int flags, void*);

int main(void)
{

	home = cv::Mat::zeros(cv::Size(LENGTH, WIDE), CV_8UC3); //刷新地图

	cv::putText(home,
							"Welcome to GSnake!",
							cv::Point(32, 64),
							7,
							1.7,
							cv::Scalar(255, 255, 255),
							2);
	
	cv::putText(home,
							"Start",
							cv::Point(200, 180),
							7,
							1.7,
							cv::Scalar(255, 180, 255),
							2);

	cv::putText(home,
							"Test",
							cv::Point(210, 240),
							7,
							1.7,
							cv::Scalar(255, 180, 255),
							2);

	cv::putText(home,
							"Out",
							cv::Point(210, 340),
							7,
							1.7,
							cv::Scalar(255, 180, 255),
							2);

   cv::imshow("window", home);


	cv::setMouseCallback("window", mouse);

	cv::waitKey(0);



    std::cout << "vsfgfv" << std::endl;



	
	return 0;
}

void mouse(int event, int x, int y, int flags, void*)
{
	if (tips)
	{
		if (x >=215 && x <= 300 && y >= 300 && y <= 350)
		{
			cv::putText(home,
								"Out",
								cv::Point(210, 340),
								7,
								1.7,
								cv::Scalar(255, 255, 255),
								2);

			cv::imshow("window", home);

			
			if (event == cv::EVENT_LBUTTONDOWN)
			{
				tips = false;
				exit(100);  //终止程序

			}
		}
		else if (x >=200 && x <= 320 && y >= 150 && y <= 180)
		{
			cv::putText(home,
								"Start",
								cv::Point(200, 180),
								7,
								1.7,
								cv::Scalar(255, 255, 255),
								2);

			cv::imshow("window", home);

			
			if (event == cv::EVENT_LBUTTONDOWN)
			{
				tips = false;

				//创建类对象
        		Game game;
				GSnake snake;

				snake << 1;

        		snake.start();
			}
		}
		else if (x >=230 && x <= 300 && y >= 185 && y <= 240)
		{
			cv::putText(home,
								"Test",
								cv::Point(210, 240),
								7,
								1.7,
								cv::Scalar(255, 255, 255),
								2);

			cv::imshow("window", home);

			
			if (event == cv::EVENT_LBUTTONDOWN)
			{
				tips = false;

				//创建类对象
        		Game game;
				GSnake snake;

				snake << 2;

        		snake.start();
			}
		}
		else
		{
			cv::putText(home,
							"Start",
							cv::Point(200, 180),
							7,
							1.7,
							cv::Scalar(255, 180, 255),
							2);

			cv::putText(home,
								"Test",
								cv::Point(210, 240),
								7,
								1.7,
								cv::Scalar(255, 180, 255),
								2);

			cv::putText(home,
									"Out",
									cv::Point(210, 340),
									7,
									1.7,
									cv::Scalar(255, 180, 255),
									2);

			cv::imshow("window", home);
		}
	}

}
