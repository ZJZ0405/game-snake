#include<iostream>
#include"Game.hpp"
#include"GSnake.hpp"

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
	int choice = 1;
	cout << "贪吃蛇" << endl
	     << "==========选择=========" << endl
	     << "1. 开始" << endl
	     << "2. 测试模式" << endl
	     << "3. 退出" << endl
	     << ": ";
	cin >> choice;
	
	if (choice == 3)
	{
		return 0;
	}
	else if (choice == 1)
	{

		
		//创建类对象
        Game game;
		GSnake snake;

        snake.start();
			
		}




	return 0;
}