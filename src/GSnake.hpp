#ifndef GSNAKE_HPP_
#define GSNAKE_HPP_


#include<iostream>
#include"Game.hpp"
#include<unistd.h> //时间间隔

const int R = 4;    //蛇的圆半径
/*
以目前算法地图长宽只能取相同值
*/
const int LENGTH = 512;     //显示窗口长(像素)
const int WIDE = 512;           //显示窗口宽(像素)

const int M_LENGTH = 100;//地图大小
const int M_WIDE = 100;//地图大小




class GSnake : public Game
{
private:
    int Direction; 	          //蛇头方向，上：1，下：2，左：3，右：4
	int Direction_backup;		//存储上一次蛇头方向，防止某些**让蛇头向后转自杀

	int TrueLong;				   //蛇真实长度

	int MaxLong;		//蛇的最大长度
    
    bool note;		//食物是否被吃掉

    multiplePoint boundary;

    singlePoint head;
    multiplePoint body;

    singlePoint food;

    cv::Mat map;

   int  choice; //启动模式



public:
    GSnake();

    bool start(void);

    bool tip(void);

    bool showMiniMap(void);

    inline void refresh(void);

    bool operator<<(int  num);

};

#endif