#include <string>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct node
{
	int x, y;
	node* next;
};

node* add(node** head, int x2, int y2);

void settingmove2(node** head, int x1, int y1, int size);

int settingmovex(int x1, int compas);

int settingmovey(int y1, int compas);

int main()
{
	srand(time(NULL));
	node* head = NULL; Event ev; bool posicion = true;
	int x1 = 5, x2 = 165, y1 = 5, y2 = 165, size = 1;
	int compas = 1, x22 = 0, y22;
	node* pseudo = head;
	int stonex[20], stoney[20];


	if (head == NULL)
	{
		node* stack = new node;
		stack->x = 0;
		stack->y = 0;
		stack->next = head;
		head = stack;
	}

	for (int i = 0; i < 20; i++)
	{
		x22 = rand() % 124;
		y22 = rand() % 61;

		stonex[i] = 5 + (8 * x22);
		stoney[i] = 5 + (8 * y22);
	}

	RenderWindow window(VideoMode(1000, 500), "Snake game");
	while (window.isOpen())
	{

		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
				window.close();
		}

		if (x2 == x1 && y2 == y1)
		{
			size++;
			add(&head, x2, y2);
			
			x22 = rand() % 124;
			y22 = rand() % 61;

			x2 = 5 + (8 * x22);
			y2 = 5 + (8 * y22);

			for (int i = 0; i < 20; i++) 
			{
				if (x2 == stonex[i] && y2 == stoney[i])
				{
					x22 = rand() % 124;
					y22 = rand() % 61;

					x2 = 5 + (8 * x22);
					y2 = 5 + (8 * y22);
				}
			}
				
		}

		x1 = settingmovex(x1, compas);
		y1 = settingmovey(y1, compas);
		settingmove2(&head, x1, y1, size);
			
			string path = "snake.png";
			string pat = "food.png";
			string pa = "stone.png";
			string p = "background.png";

			Texture Food;
			Texture Snake;
			Texture Stone;
			Texture background;

			Food.loadFromFile(pat);
			Snake.loadFromFile(path);
			Stone.loadFromFile(pa);
			background.loadFromFile(p);

			Sprite Sprite2(Food);
			Sprite Sprite1(Snake);
			Sprite Sprite3(Stone);
			Sprite Sprite4(background);

			Sprite2.setPosition(x2, y2);
			window.draw(Sprite4);
				node* pseudo = head;
				for (int i = 1; i <= size; i++)
				{
					if (pseudo->next == NULL)
					{
						Sprite1.setPosition(pseudo->x, pseudo->y);
						for (int i = 0; i < 20; i++)
						{
							Sprite3.setPosition(stonex[i], stoney[i]);
							window.draw(Sprite3);
						}
						window.draw(Sprite2);
						window.draw(Sprite1);
					}
					else
					{
						Sprite1.setPosition(pseudo->x, pseudo->y);
						for (int i = 0; i < 20; i++)
						{
							Sprite3.setPosition(stonex[i], stoney[i]);
							window.draw(Sprite3);
						}
						window.draw(Sprite2);
						window.draw(Sprite1);

						pseudo = pseudo->next;
					}
				}
				
				for (int i = 0; i < 20; i++)
				{
					if (stonex[i]==x1 && stoney[i]==y1) 
					{
						return 0;
					}
				}

				//Не реализованная функция столкновения змейки с самим собой
				/*node* boom = head;
				for (int i = 1; i <= size; i++)
				{
					if (pseudo->next == NULL)
					{
						break;
					}

					if (x1 == boom->next->x && y1 == boom->next->y)
					{
						return 0;
					}
					boom = boom->next;
				}*/
			
			window.display();
			Sleep(100);
			window.clear(Color::White);

		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			compas = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			compas = 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			compas = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) 
		{
			compas = 4;
		}
	}

	return 0;

}

node* add(node** head, int x2, int y2)
{
	node* stack = new node;
	stack->x = x2;
	stack->y = y2;
	stack->next = *head;
	*head = stack;
	return stack;
}

void settingmove2(node** head, int x1, int y1, int size)
{
	node* pseudo = *head;
	for (int i = 1; i <= size; i++)
	{
		if (pseudo->next == NULL)
		{
			pseudo->x = x1;
			pseudo->y = y1;
		}
		else
		{
			pseudo->x = pseudo->next->x;
			pseudo->y = pseudo->next->y;
			pseudo = pseudo->next;
		}
	}
}

int settingmovex(int x1, int compas)
{
	int step = 8;
	if (compas == 1)
	{
		x1 += step;
	}
	if (compas == 2)
	{
		x1 -= step;
	}
	return x1;
}

int settingmovey(int y1, int compas)
{
	int step = 8;
	if (compas == 3)
	{
		y1 -= step;
	}
	if (compas == 4)
	{
		y1 += step;
	}
	return y1;
}