#include"GSnake.hpp"



GSnake::GSnake()
{
	//初始化变量

	note = false;

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
            break;
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
			std::cout << food.x << " , " << food.y << std::endl;
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

