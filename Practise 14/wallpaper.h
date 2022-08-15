#pragma once
#ifndef WALLPAPER_H
	#define WALLPAPER_H
	#include <iostream>
	#include <fstream>
	#include <string>
	#include <Windows.h>
	using namespace std;
	struct wallpaper {
		int length;				//Длина рулона
		int width;				//Ширина рулона
		string picture;			//Есть ли рисунок на обоях
		string canvas;			//Тип полотна
		string date;			//Дата изготовления
		int expiration_date;	//Срок годности
		string density;			//Плотность
		float cost;				//Цена за рулон
	};
	struct wallpaperNode {
		wallpaper Data;
		wallpaperNode* next = NULL;
		wallpaperNode* prev = NULL;
	};
	static string database = "Wallpaper.dat";
	static string txt_table = "wallpaper.txt";
	static string csv_table = "wallpaper.csv";
	void input_data();
	void output_data();
	void min_cost();
	int table();
	int export_data();
	void create_root(wallpaperNode* node);
	void erase_root(wallpaperNode* node);
	void show_root(wallpaperNode* node);
#endif