#include"Game.hpp"

Game::Game()
{
    ch = 'd';

}

int Game::getKey(void)
{
    ch = cv::waitKey(1); //读取键盘输入
		
	switch (ch)	//改变方向
	{
		case 'w':
			return 1;
			break;
			
		case 's':
			return 2;
			break;
			
		case 'a':
			return 3;
			break;
			
		case 'd':
			return 4;
			break;
		case 'o':
			exit(200);
		default:
			return 0;
			break;
	}
}



bool Game::output(const cv::Mat & background) const
{
	cv::imshow("window", background);		//输出	

	return false;
}

int Game::random(int start, int end)
{
	return (rand() % (end - start + 1)) + start;
}

bool Game::change(const singlePoint * center, const singlePoint * single, const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & R) const
{
	if (single->kind == 1)
	{
		cv::circle(
		background, //地图矩阵
		cv::Point(2*R*(single->x + LENGTH/(4*R) - center->x),(2*R*(single->y + (WIDE/(4*R)) - center->y))), //圆心坐标
		R, //圆半径
		cv::Scalar(0, 255, 255), //颜色
		-1, //空心圆
		CV_MSA /*用于抗锯齿？？？*/);
	}
	return false;
}

bool Game::change(const singlePoint * center, const multiplePoint * multipe, const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & R) const
{
	if (multipe->kind == 1)
	{
		for (int i = 0; i < multipe->x.size(); i++)
    	{
        	cv::circle(
			background, //地图矩阵
			cv::Point(2*R*(multipe->x[i] + LENGTH/(4*R) - center->x),(2*R*(multipe->y[i] + (WIDE/(4*R)) - center->y))), //圆心坐标
			R, //圆半径
			cv::Scalar(0, 0, 255), //颜色
			-1, //实心圆
			CV_MSA /*用于抗锯齿？？？*/);
		}
	}
	else if (multipe->kind == 2)
	{
		for (int i = 0; i <multipe->x.size(); i++)
		{
			cv::circle(
			background, //地图矩阵
			cv::Point(2*R*(multipe->x[i] + LENGTH/(4*R) - center->x),(2*R*(multipe->y[i] + (WIDE/(4*R)) - center->y))), //圆心坐标
			R, //圆半径
			cv::Scalar(255, 255, 255), //颜色
			-1, //实心圆
			CV_MSA /*用于抗锯齿？？？*/);		
		}
	}

	return false;
}

bool Game::showNumber(const cv::Mat & background, const int & LENGTH, const int & WIDE, const int & Num, int kind) const
{
	switch (kind)
	{
	case 2:
		cv::putText(background, 
								 std::to_string(Num),
								 cv::Point(LENGTH - 50, 50),
								 0,
								 1,
								 cv::Scalar(255, 255, 255)
								 );
		break;
	
	default:
		break;
	}

	return false;
}

