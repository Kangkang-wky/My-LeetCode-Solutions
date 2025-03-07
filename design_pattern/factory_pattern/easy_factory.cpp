#include "../include/help.h"

//文具类（抽象产品）
class Stationery {
public:
	virtual void use() = 0;
	virtual ~Stationery() {}
};
 
//钢笔类（具体产品）
class Pen :public Stationery {
public:
	Pen() {
		cout << "Pen()" << endl;
	}
	virtual ~Pen() {
		cout << "~Pen()" << endl;
	}
	virtual void use() override{
		cout << "Use pen." << endl;
	}
};
 
//铅笔类（具体产品）
class Pencil :public Stationery {
public:
	Pencil() {
		cout << "Pencil()" << endl;
	}
	virtual ~Pencil() {
		cout << "~Pencil()" << endl;
	}
	virtual void use() override {
		cout << "Use pencil." << endl;
	}
};
 
//枚举类型
enum StationeryType {
	PEN,
	PENCIL
};
 
//文具工厂类
class StationeryFactory {
public:
	static shared_ptr<Stationery> createStationery(StationeryType type) {
		switch (type) {
		case PENCIL:
			return shared_ptr<Stationery>(new Pencil);
			break;
		case PEN:
			return shared_ptr<Stationery>(new Pen);
			break;
		defalut:
			return nullptr;
			break;
		}
	}
};