#include"GSnake.hpp"



GSnake::GSnake()
{
	//初始化变量

	note = false;

	choice = 1;

    //boundary

    head = {0, 0, 0};
    //body = {0, 0, 0};

    food = {0, 0, 1};

    body.kind = 2;
    boundary.kind = 1;
    //构建边界
    for (int i = -M_LENGTH; i < M_LENGTH; i++)
	{
			boundary.x.push_back(i);   boundary.y.push_back(M_WIDE);
	}
	for (int i = -M_LENGTH; i < M_LENGTH; i++)
	{
		    boundary.x.push_back(i);   boundary.y.push_back(-M_WIDE);
	}
    for (int i = -M_WIDE; i < M_WIDE; i++)
	{
		    boundary.x.push_back(M_LENGTH);   boundary.y.push_back(i);
	}
	for (int i = -M_WIDE; i < M_WIDE; i++)
	{
		    boundary.x.push_back(-M_LENGTH);   boundary.y.push_back(i);
	}
    
    map = cv::Mat::zeros(cv::Size(LENGTH, WIDE), CV_8UC3);

	Direction = 4; //默认向右
	Direction_backup = 4;
	

	TrueLong = 0;  //蛇的真实长度
	MaxLong = 2;	  //蛇的最大长度



}

bool GSnake::start(void)
{
    while(true)
    {
        if (tip())
		{
            cv::Mat home = cv::Mat::zeros(cv::Size(LENGTH, WIDE), CV_8UC3); //刷新地图

			cv::putText(home,
									"You lose!!!",
									cv::Point(64, 256),
									7,
									2,
									cv::Scalar(0, 0, 255),
									2);
			cv::imshow("window", home);
			cv::waitKey(50);
			break;
		}
        //时间间隔 0.3秒
		usleep(300000);
		//sleep(1);
		//std::cout << head.x << " , " << head.y << std::endl;
    }
    return 0;

}

bool GSnake::tip(void)
{
	if (note == false)
	{
		do
		{
			food.x = random(head.x - LENGTH/(4*R),head.x + LENGTH/(4*R));
			food.y = random(head.y - WIDE/(4*R),head.y + WIDE/(4*R));
			note = true;

			if (choice == 2) std::cout <<  "Food: " << food.x << " , " << food.y << std::endl; //调试输出

		}while(abs(food.x) >= M_LENGTH || abs(food.y) >= M_WIDE);
	}
    //移动蛇头
    Direction = getKey();

	if (Direction == 0)
		Direction = Direction_backup;
	
	//Direction_backup = Direction 进行防蠢变量存储
	switch (Direction)
	{
		case 1:
			if (Direction_backup == 2)  
			{
				head.y += 1;
				break;
			}
			{
			head.y -= 1;
			Direction_backup = Direction;
			break;
			}
			

		case 2:
			if (Direction_backup == 1) 
			{
				head.y -= 1;
				break;
			}
			{
			head.y += 1;
			Direction_backup = Direction;
			break;
			}
			
					
		case 3:
			if (Direction_backup == 4) 
			{
				head.x += 1; 
				break;	
			}
			{
			head.x -= 1; 
			Direction_backup = Direction;
			break;
			}
			
					
		case 4:
			if (Direction_backup == 3) 
			{
				head.x -= 1;
				break;
			}
			{
			head.x += 1;
			Direction_backup = Direction;
			break;
			}
			
	}

	if (choice == 2) std::cout <<  "Head: " << head.x << " , " << head.y << std::endl; //调试输出

	if ((abs(head.x) >= M_LENGTH) || (abs(head.y) >= M_WIDE))
	{
		std::cout << "you lose!!!" << std::endl;
		return true;				//触及边界结束函数，并输入伪信号终止while循环
	}
	else		
	{
		for (int i = 0; i < body.x.size(); i++)	         //判断是否触及身体
		{
			if ((body.x[i] == head.x) && (body.y[i] == head.y))//若触及
			{
				std::cout << "you lose!!!" << std::endl;
				return true;				//触及身体结束函数，并输入伪信号终止while循环
			}
		}
	}
	
	if ((head.x == food.x) && (head.y == food.y))
	{
		MaxLong++;
		note = false;
	}	
	
/*
固定蛇长度
使用vector实现队列的出队与入队
*/
	if (TrueLong < MaxLong)
	{
		TrueLong++;  //蛇真实长度增加
		
		body.x.insert(body.x.begin(), head.x);	body.y.insert(body.y.begin(), head.y); //蛇头计入蛇身(入队)
	}
	else
	{
		body.x.pop_back();		body.y.pop_back();  	//去尾(出队)
		
		body.x.insert(body.x.begin(), head.x);	body.y.insert(body.y.begin(), head.y); //蛇头计入蛇身(入队)
	}

	refresh();
	showNumber(map, LENGTH, WIDE, TrueLong, 2);
	showMiniMap();
    change(&head, &food, map, LENGTH, WIDE, R);		
	change(&head, &boundary, map, LENGTH, WIDE, R);
	change(&head, &body, map, LENGTH, WIDE, R);
	output(map);
			
	return false;
}

inline void GSnake::refresh(void)
{
    map = cv::Mat::zeros(cv::Size(LENGTH, WIDE), CV_8UC3); //刷新地图
}

bool GSnake::showMiniMap(void)
{
	cv::rectangle(map, 
								 cv::Point(0, 0),
								 cv::Point(100, 100),
								 cv::Scalar(255, 255, 255)); //画出小地图轮廓

	cv::circle(map,
						cv::Point(50, 50),
						1,
						cv::Scalar(255, 255, 255),
						-1);  //蛇头标点

	if (abs(head.x - food.x) <=50 && abs(head.y - food.y) <= 50)
	{
		cv::circle(map,
							cv::Point((50 + (food.x - head.x)), (50 + (food.y - head.y))),  // 蛇走两格， 地图走一格
							1,
							cv::Scalar(0, 0, 255),
							-1);  //食物
	}
	else
	{
		if (food.x - head.x> 50)
		{
			if (food.y - head.y > 50)
			{
				//右下
				cv::line(map,
								cv::Point(100, 100),
								cv::Point(100, 75),
				 				cv::Scalar(255, 255, 0));
				cv::line(map,
								cv::Point(100, 100),
								cv::Point(75, 100),
								cv::Scalar(255, 255, 0));
			}
			else if (abs(food.y - head.y) <= 50)
			{
				//右
				cv::line(map,
								cv::Point(100, 25),
				 				cv::Point(100, 75),
				 				cv::Scalar(255, 255, 0));
			}
			else if (food.y - head.y < -50)
			{
				//右上
				cv::line(map,
				 				cv::Point(100, 0),
				 				cv::Point(75, 0),
				 				cv::Scalar(255, 255, 0));
				cv::line(map,
								cv::Point(100, 0),
								cv::Point(100, 25),
								cv::Scalar(255, 255, 0));       
			}
		}
		else if (abs(food.x - head.x) <= 50)
		{
			if (food.y - head.y > 50)
			{
				//下
				cv::line(map,
				 				cv::Point(25, 100),
				 				cv::Point(75, 100),
				 				cv::Scalar(255, 255, 0));
			}
			else if (food.y - head.y < -50)
			{
				//上
				cv::line(map,
				 				cv::Point(25, 0),
				 				cv::Point(75, 0),
				 				cv::Scalar(255, 255, 0));
			}
		}
		else if (food.x - head.x < -50)
		{
			if (food.y - head.y > 50)
			{
				//左下
				cv::line(map,
				 				cv::Point(0, 100),
								cv::Point(25, 100),
				 				cv::Scalar(255, 255, 0));
					cv::line(map,
									cv::Point(0, 100),
									cv::Point(0, 75),
									cv::Scalar(255, 255, 0));     
			}
			else if (abs(food.y - head.y) <= 50)
			{
				//左
				cv::line(map,
				 				cv::Point(0, 25),
				 				cv::Point(0, 75),
				 				cv::Scalar(255, 255, 0));
			}
			else if (food.y - head.y < -50)
			{
				//左上
				cv::line(map,
								cv::Point(0, 0),
								cv::Point(25, 0),
								cv::Scalar(255, 255, 0));
					cv::line(map,
									cv::Point(0, 0),
									cv::Point(0, 25),
									cv::Scalar(255, 255, 0));    
			}
		}
	}

	
	

	return false;
}

bool GSnake::operator<<(int  num)  //启动模式输入
{
	choice = num;

	return false;
}
