#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define MAX_X 8
#define MAX_Y 8
#define CONTEXT_MENU_X 80
#define CONTEXT_MENU_Y 120


class Obj
{
public:
	friend class Game;

	Obj(std::string object_name, unsigned object_quantity, unsigned short object_type , unsigned obj_size, olc::Pixel obj_color= olc::WHITE)
	{
		obj_name = object_name;
		this->obj_type = object_type;
		size = obj_size;
		color = obj_color;
		this->quantity = object_quantity;
	}

	Obj(const Obj& self)
	{
		this->obj_name = self.obj_name;
		this->obj_type = self.obj_type;
		this->size = self.size;
		this->color = self.color;
		this->quantity = self.quantity;
	}

	friend bool operator== (const Obj& a, const Obj& b);

	enum object
	{
		SHAPE = 1,
		TEXTURE = 2,
		DECAL = 3,
	};

	virtual void* getObj() = NULL;

	virtual unsigned getSize()
	{
		return size;
	}
	
	std::string get_name()
	{
		return obj_name;
	}

	unsigned short getObjType()
	{
		return obj_type;
	}

private:
	unsigned size;
	unsigned short obj_type;
	olc::Pixel color;
	std::string obj_name;
	unsigned quantity;

};

class NullObj : public Obj
{
public:
	NullObj() :Obj(" ", 0, 0, 0,olc::MAGENTA)
	{

	}

	virtual void* getObj()
	{
		return 0;
	}

	unsigned short getObjType()
	{
		return 0;
	}
	
};

class Shape : public Obj
{
public:
	enum type
	{
		REC = 1,
		CIRCLE = 2,
	};

	Shape(std::string object_name, unsigned object_quantity, unsigned short object_type, olc::Pixel color, unsigned obj_size, unsigned shape_type) :Obj(object_name, object_quantity, object_type, obj_size, color)
	{
		this->shape_type = shape_type;
	}

	Shape(const Shape& self) :Obj(self)
	{
		this->shape_type = self.shape_type;
	}

	void* getObj() override
	{
		return &shape_type;
	}

private:

	unsigned shape_type;

};

class Texture : public Obj
{
public:

	Texture(std::string object_name, unsigned object_quantity, unsigned short object_type, unsigned obj_size, std::string sprite_path, olc::Pixel obj_color = olc::WHITE) :Obj(object_name, object_quantity, object_type, obj_size , obj_color)
	{
		picture = std::make_unique<olc::Sprite>(sprite_path);
		texture_path = sprite_path;
	}

	Texture(const Texture& self) :Obj(self)
	{
		picture = std::make_unique<olc::Sprite>(self.texture_path);
		this->texture_path = self.texture_path;
	}

	void* getObj() override
	{
		return picture.get();
	}

private:
	std::unique_ptr<olc::Sprite> picture;
	std::string texture_path;
};

bool operator== (const Obj& a, const Obj& b)
{
	if ((a.obj_name.compare(b.obj_name) == 0) && (a.obj_type == b.obj_type) && (a.size == b.size))
	{
		return true;
	}
	else
	{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "Example";
		mousePos.x = 0;
		mousePos.y = 0;

		notStollen = false;

		inv = new Obj * *[MAX_X];
		for (int i = 0; i < MAX_X; i++)
		{
			inv[i] = new Obj * [MAX_Y];
			for (int j = 0; j < MAX_Y; j++)
			{
				inv[i][j] = &nothing;
			}
		}

		inv[2][2] = new Shape("Clown nose", 5, 1, olc::RED, 12, 2);
		inv[7][2] = new Shape("Clown nose", 5, 1, olc::RED, 12, 2);
		inv[4][4] = new Texture("Fresh sword", 1, 2, 16, "IconAttack.png", olc::BLACK);
		inv[4][5] = new Texture("Heal Potion", 1, 2, 16, "IconHeal.png", olc::BLACK);
		inv[3][5] = new Texture("Dodge Spell", 1, 2, 16, "IconDodge.png", olc::BLACK);
		inv[2][5] = new Texture("Shield", 1, 2, 16, "IconBlock.png", olc::BLACK);
		inv[1][5] = new Texture("Fastest legs Spell", 1, 2, 16, "IconFlee.png", olc::BLACK);
		inv[0][5] = new Texture("false teeth", 1, 2, 16, "IconBite.png", olc::BLACK);
		inv[0][5] = new Texture("Blood String's", 1, 2, 16, "IconClaw.png", olc::BLACK);

		buffItem = &nothing;

		lastX = 0;
		lastY = 0;

		ContextCord.x = 0;
		ContextCord.y = 0;

		randvec.x = 0;
		randvec.y = 100;

		ContextMenu = false;
	}

	bool OnUserCreate() override
	{
		SetPixelMode(olc::Pixel::MASK);
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_GREEN);
		mousePos = GetMousePos();

		if (GetMouse(0).bPressed)
		{
			if (ContextMenu == true)
			{
				if (mousePos.x >= ContextCord.x && mousePos.x <= ContextCord.x + CONTEXT_MENU_X && mousePos.y >= ContextCord.y && mousePos.y <= ContextCord.y + CONTEXT_MENU_Y)
				{
					if (mousePos.y <= ContextCord.y + 20)
					{
						Obj* cur = inv[int((ContextCord.x - 8) / 48)][int((ContextCord.y - 8) / 48)];
						
						switch (cur->getObjType())
						{
						case 1:
							stomach.push_back(new Shape(*(Shape*)(cur)));
							break;
						case 2:
							stomach.push_back(new Texture(*(Texture*)(cur)));
							break;
						default:
							break;
						}
						inv[int((ContextCord.x - 8) / 48)][int((ContextCord.y - 8) / 48)] = &nothing;
						
					}
					else if (mousePos.y <= ContextCord.y + 40)
					{
						if (inv[int((ContextCord.x - 8) / 48)][int((ContextCord.y - 8) / 48)]->quantity > 1)
						{
							Obj* cur = inv[int((ContextCord.x - 8) / 48)][int((ContextCord.y - 8) / 48)];
							switch (cur->getObjType())
							{
							case 1:
								buffItem = new Shape(*(Shape*)(cur));
								break;
							case 2:
								buffItem = new Texture(*(Texture*)(cur));
								break;
							default:
								break;
							}
							buffItem->quantity = cur->quantity / 2;
							cur->quantity -= buffItem->quantity;
							notStollen = true;
						}
					}
					else if (mousePos.y <= ContextCord.y + 60)
					{
						Obj* cur = inv[int((ContextCord.x - 8) / 48)][int((ContextCord.y - 8) / 48)];
						switch (cur->getObjType())
						{
						case 1:
							buffItem = new Shape(*(Shape*)(cur));
							break;
						case 2:
							buffItem = new Texture(*(Texture*)(cur));
							break;
						default:
							break;
						}
						notStollen = true;

					}
					ContextMenu = false;
				}
				else
				{
					ContextMenu = false;
				}
			}
			else if (((mousePos.x - 8) / 48) >= 0 && ((mousePos.y - 8) / 48) >= 0 && ((mousePos.x - 8) / 48) <= MAX_X - 0.1f && ((mousePos.y - 8) / 48) <= MAX_Y - 0.1f)
			{

				if (buffItem == &nothing)
				{
					buffItem = inv[(int((mousePos.x - 8) / 48))][(int((mousePos.y - 8) / 48))];
					inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] = &nothing;
					lastX = abs(int((mousePos.x - 8) / 48));
					lastY = abs(int((mousePos.y - 8) / 48));

				}
				else if (*buffItem == *inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] && (inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)]->quantity + buffItem->quantity < 65))
				{
					if (notStollen == false)
					{
						Obj* deleter = buffItem;
						inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)]->quantity += buffItem->quantity;
						inv[lastX][lastY] = &nothing;
						buffItem = &nothing;
						delete deleter;
					}
					else
					{
						inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)]->quantity += buffItem->quantity;
						Obj* deleter = buffItem;
						buffItem = &nothing;
						delete deleter;
					}
				}
				else if(notStollen == false)
				{
					//inv[lastX][lastY] = inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)];
					std::swap(inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] , buffItem);
					//buffItem = &nothing;
				}
				else
				{
					if (*inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] == nothing)
						//
						// ТУТ БАГ ЧТО КЛОНИРОВАННЫЙ/РАЗДЕЛЕННЫЙ ПРЕДМЕТ УДАЛЯЕТ ПРЕДМЕТ ДРУГОГО ВИДА НА КОТОРЫЙ ОН СТАВИТСЯ
						// фикс либо перемещения в свободную клекту (с невидимым инвентарем ака сталкрафт) или запретом (мега кринж)
					{
						inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] = buffItem;
						buffItem = &nothing;
						notStollen = false;
					}
					else
					{
						std::swap(inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)], buffItem);
						
					}
					
				}
			}

		}
		if (GetMouse(1).bPressed)
		{
			if (((mousePos.x - 8) / 48) >= 0 && ((mousePos.y - 8) / 48) >= 0 && ((mousePos.x - 8) / 48) <= MAX_X - 0.1f && ((mousePos.y - 8) / 48) <= MAX_Y - 0.1f)
			{
				if (inv[int((mousePos.x - 8) / 48)][int((mousePos.y - 8) / 48)] != &nothing)
				{
					ContextMenu = true;
					ContextCord = mousePos;
				}
				else
				{
					ContextMenu = false;
				}
			}
			else
			{
				ContextMenu = false;
			}
		}

		DisplayInv();
		if (buffItem != &nothing)
		{
			DisplayItem(buffItem, mousePos.x, mousePos.y);
			FillRect(420, 440, 10, 10, olc::GREEN);
		}
		DrawString(16, 460, std::to_string((mousePos.x - 8) / 48) + " " + std::to_string((mousePos.y - 8) / 48), olc::WHITE);
		DrawString(16, 445, std::to_string(ContextCord.x) + " " + std::to_string(ContextCord.y), olc::WHITE);
		DrawString(16, 430, std::to_string(mousePos.x) + " " + std::to_string(mousePos.y), olc::WHITE);
		if ((int((mousePos.x - 8) / 48)) < MAX_X && (int((mousePos.y - 8) / 48)) < MAX_Y)
			DrawString(mousePos.x + 16, mousePos.y, inv[(int((mousePos.x - 8) / 48))][(int((mousePos.y - 8) / 48))]->get_name(), olc::WHITE);
		DisplayStomach();


		if (ContextMenu == true) DisplayContextMenu();

		return true;

	}

	~Game()
	{
		if (buffItem != &nothing)
		{
			delete buffItem;
		}

		for (int i = 0; i < MAX_X; i++)
		{
			for (int j = 0; j < MAX_Y; j++)
			{
				if (inv[i][j] != &nothing)
				{
					delete inv[i][j];
				}
			}
			delete[] inv[i];
		}
		delete[] inv;

	}

private:
	olc::vd2d mousePos;
	olc::vd2d randvec;

	olc::vd2d ContextCord;

	unsigned short lastX;
	unsigned short lastY;

	bool ContextMenu;
	bool notStollen;

	Obj* buffItem;

	Obj*** inv;

	std::vector<Obj*> stomach;

	NullObj nothing;

	friend class Obj;
	friend class Texture;
	friend class Shape;

	void DisplayInv()
	{
		for (int i = 0; i < MAX_X; i++)
		{
			for (int j = 0; j < MAX_Y; j++)
			{
				FillRect((48 * i) + 8, (48 * j) + 8, 40, 40, olc::BLACK);
				DrawRect((48 * i) + 8, (48 * j) + 8, 40, 40, olc::WHITE);


				DisplayItem(inv[i][j], (48 * i) + 28, (48 * j) + 28);
			}
		}
	}

	void DisplayContextMenu()
	{
		FillRect(ContextCord, olc::vi2d(CONTEXT_MENU_X, CONTEXT_MENU_Y), olc::BLACK);
		DrawRect(ContextCord, olc::vi2d(CONTEXT_MENU_X, CONTEXT_MENU_Y), olc::WHITE);
		for (int i = 1; i < 5; i++)
		{
			DrawRect(ContextCord.x, ContextCord.y + 20 * i, CONTEXT_MENU_X, 20, olc::WHITE);
		}
		DrawString(ContextCord.x + 8, ContextCord.y + 7, "Eat");
		DrawString(ContextCord.x + 8, ContextCord.y + 27, "Split");
		DrawString(ContextCord.x + 8, ContextCord.y + 47, "Clone");
		FillRect(440, 440, 10, 10, olc::RED);
	}

	void DisplayItem(Obj* object, int x, int y)
	{
		if (object != &nothing)
		{
			switch (object->getObjType())
			{
			case 1:
				return DisplayShape(object, x, y);
				break;
			case 2:
				return DisplayTexture(object, x, y);
				break;
			}
		}
	}

	void DisplayStomach()
	{
		if (stomach.size() > 8)
		{
			while (stomach.size() > 8) stomach.erase(stomach.begin());
		}
		for (int i = 0; i < stomach.size(); i++) 
		{
			DisplayItem(stomach[i], 440, (i * 48) + 16);
		}
	}

	void DisplayShape(Obj* object, int x, int y)
	{
		unsigned cur_shape = *(unsigned*)object->getObj();
		std::string quantity = std::to_string(object->quantity);
		
		switch (cur_shape)
		{
		case 1:
			FillRect(x, y, object->size, object->size, object->color);
			break;
		case 2:
			FillCircle(x, y, object->size, object->color);
			break;
		default:
			FillRect(x, y, 20, 20, olc::MAGENTA);
			break;
		}
		if (quantity.size() > 1) x -= 8;
		DrawString(x + 12, y + 12, std::to_string(object->quantity));
	}

	void DisplayTexture(Obj* object, int x, int y)
	{
		std::string quantity = std::to_string(object->quantity);
		DrawSprite(x - object->size, y - object->size, (olc::Sprite*)object->getObj(), 2, 0);
		if (quantity.size() > 1) x -= 8 * (quantity.size() - 1);
		DrawString(x + 12, y + 12, std::to_string(object->quantity));
	}

};

int main()
{
	Game go;
	if (go.Construct(480, 480, 2, 2, false, true))
	{
		go.Start();
	}

	return 0;
}

