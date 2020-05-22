#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "includeAll.h"
#include "myMath.h"
#include <charconv>




void drawStuff();
void checkPlayerMovement();
void updateDraw();
void checkCollisions(Character*);
void transformProps(int dx, int dy);
void printPositions();
void drawInventory();



Character* player = NULL;
ALLEGRO_COLOR bgcol;
propArray* propArr; //array that holds all props in the scene
InvCell* invHead = NULL;
Inventory* inventory = NULL;
Prop* backgroundGrass;
Prop* dummyProp = NULL;
Prop* dummyProp1 = NULL;
Prop* dummyProp2 = NULL;
Prop* dummyProp3 = NULL;


ALLEGRO_DISPLAY* display = NULL;
Camera* camera = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_FONT* invFont = NULL;



enum KEYS {UP, DOWN, LEFT, RIGHT};
bool keys[4] = { false, false, false, false };
bool redraw = false;
bool endgame = false;
bool drawInv = false;



//all obects are in world coordinates
//camera is in camera coordinates


int main() {
	//initialize allegro
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	//initialize stuff
	const int FPS = 60;
	display = al_create_display(SCRN_W, SCRN_H);
	bgcol = al_map_rgb(123, 213, 312);
	font = al_load_font("../fonts/Gabriola.ttf", 25, 0);
	invFont = al_load_font("../fonts/Gabriola.ttf", 20, 0);
	


	//event queue
	event_queue = al_create_event_queue();
	timer = al_create_timer(1. / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


	//create objects
	player = new Character("player", al_load_bitmap("../bitmaps/player.jpg"), 64, 64, SCRN_W/2, SCRN_H/2, 5, 5);
	
	invHead = new InvCell(NULL, "head", -1);
	inventory = new Inventory(al_load_bitmap("../bitmaps/inventory.png"),invHead);
	
	camera = new Camera(0,0); //different coordinate system
	
	backgroundGrass = new Prop("grass", "ground",al_load_bitmap("../bitmaps/grass.jpg"), 1000, 1000, WORLD_CX, WORLD_CY);
	
	dummyProp = new Prop("dummy", "pickUp", al_load_bitmap("../bitmaps/dummyProp.png"), 32, 32, WORLD_CX + 100, WORLD_CY + 100);
	dummyProp1 = new Prop("dummy1", "none", al_load_bitmap("../bitmaps/dummyProp.png"), 32, 32, WORLD_CX + 100, WORLD_CY + 300);
	dummyProp2 = new Prop("dummy2", "pickUp",al_load_bitmap("../bitmaps/dummyProp.png"), 32, 32, WORLD_CX + 500, WORLD_CY + 300);
	dummyProp3 = new Prop("dummy", "pickUp",al_load_bitmap("../bitmaps/dummyProp.png"), 32, 32, WORLD_CX + 500, WORLD_CY + 500);


	//make prop array
	propArr = new propArray(5);
	propArr->append(backgroundGrass);
	propArr->append(dummyProp);
	propArr->append(dummyProp1);
	propArr->append(dummyProp2);
	propArr->append(dummyProp3);
	

	dummyProp->setInteractable(true);
	//dummyProp1->setInteractable(true);
	dummyProp2->setInteractable(true);
	dummyProp3->setInteractable(true);
	
	dummyProp->setCollidable(false);


	while (!endgame) {
	
		
		//Draw
		//printPositions();
		updateDraw();
		checkCollisions(player);


		//MOVEMENT
		checkPlayerMovement();
		
		//camera->move(player->getX() - SCRN_W / 2, player->getY() - SCRN_H / 2);


		al_flip_display();
	}

	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_event_queue(event_queue);



	return 0;
}


void updateDraw() {
	if (redraw && al_event_queue_is_empty(event_queue)) {
		redraw = false;
		al_clear_to_color(bgcol);
		drawStuff();
		al_flip_display();
	}
}

//draw things on the screen
void drawStuff() {
	//draw props
	int size = propArr->getSize();
	Prop* tmpProp = NULL;
	for (int i = 0; i < size; i++) {
		tmpProp = propArr->getElement(i);
		if (tmpProp->isActive()) {
			al_draw_bitmap(tmpProp->getBitmap(), tmpProp->getX(), tmpProp->getY(), 0);
			if (i > 0) {
				al_draw_circle(tmpProp->getX() + tmpProp->getWidth() / 2, tmpProp->getY() + tmpProp->getHeigth() / 2, 2, al_map_rgb(255, 0, 0), 2);
			}
		}
		if(player->nearTo(tmpProp) && tmpProp->isInteractable() && tmpProp->isActive())
			al_draw_text(font, al_map_rgb(255, 240, 255),player->getX() - player->getWidth(), player->getY() - player->getHeigth() / 2 - 30, 0, "Press E to interact");
	}

	if (drawInv)
		drawInventory();
	//draw Player
	al_draw_bitmap(player->getBitmap(), player->getX() - player->getWidth() / 2, player->getY() - player->getHeigth() / 2, 0);
	al_draw_circle(player->getX(), player->getY(), 2, al_map_rgb(255,0,0),2);




}


//draw the inventory on the screen
void drawInventory() {
	//int size = inventory->getSize();
	int Yspacing = 30;
	int Xspacing = 40;
	al_draw_bitmap(inventory->getBitmap(), 20, 10, 0);
	InvCell* head = inventory->getHead();
	InvCell* tmpCell = head->getNext();
	while (tmpCell) {
		Xspacing = 30;
		//al_draw_scaled_bitmap(tmpCell->getIcon(),spacing,10,30,10,spacing+10,30,10,10,0);
		//icon
		al_draw_bitmap(tmpCell->getIcon(), Xspacing, Yspacing, 0);
		Xspacing += 40;
		//name
		al_draw_text(invFont, al_map_rgb(255,240,255), Xspacing, Yspacing+5, 0, tmpCell->getName());
		//quantity
		Xspacing += 60;
		//turn int to const char
		char buf[16];
		sprintf_s(buf, "%d", tmpCell->getQuantity());
		
		al_draw_text(invFont, al_map_rgb(255,240,255), Xspacing, Yspacing+5, 0, buf);
		Yspacing += 35;
		tmpCell = tmpCell->getNext();
	}

}


void checkPlayerMovement() {
	ALLEGRO_EVENT events;
	int dx = 0;
	int dy = 0;

	al_wait_for_event(event_queue, &events);
	if (events.type == ALLEGRO_EVENT_TIMER) {
		dx = player->getSpeedX() * player->getDirectionX();
		dy = player->getSpeedY() * player->getDirectionY();
		int newX = player->getX() + dx;
		int newY = player->getY() + dy;
		Character* tmpPlayer = new Character("tmpPlayer", NULL, player->getHeigth(), player->getWidth(), newX, newY);

		//if player collides with something, they are already colliding
		//if player collides on top and direction is up
		if (player->getCollides()[COLL_UP] && dy < 0)
			dy = 0;
		//if player collides on bot and direction is down
		if (player->getCollides()[COLL_DOWN] && dy > 0)
			dy = 0;
		//if player collides on left and direction is left
		if (player->getCollides()[COLL_LEFT] && dx < 0)
			dx = 0;
		//if player collides on right and direction is right
		if (player->getCollides()[COLL_RIGHT] && dx > 0)
			dx = 0;

		//check if new position will place player in a prop
		checkCollisions(tmpPlayer);
		if (tmpPlayer->getCollides()[COLL_UP] && dy < 0)
			dy = 0;
		
		if (tmpPlayer->getCollides()[COLL_DOWN] && dy > 0)
			dy = 0;
		
		if (tmpPlayer->getCollides()[COLL_LEFT] && dx < 0)
			dx = 0;
		
		if (tmpPlayer->getCollides()[COLL_RIGHT] && dx > 0)
			dx = 0;



		//check world bounds
		if ((newX + player->getWidth()/2 > backgroundGrass->getX() + backgroundGrass->getWidth()) || (newX - player->getWidth() / 2 < backgroundGrass->getX()))
			dx = 0;
		if ((newY + player->getHeigth() / 2 > backgroundGrass->getY() + backgroundGrass->getHeigth()) || (newY - player->getHeigth() / 2 < backgroundGrass->getY()))
			dy = 0;


		transformProps(dx, dy);
		redraw = true;

	}
	else if (events.type == ALLEGRO_EVENT_KEY_UP) {
		//up
		if (events.keyboard.keycode == ALLEGRO_KEY_W || events.keyboard.keycode == ALLEGRO_KEY_UP) {
			keys[UP] = false;
			if (!keys[DOWN])
				player->setDirectionY(0);
			else
				player->setDirectionY(-1);

		}
		//down
		else if (events.keyboard.keycode == ALLEGRO_KEY_S || events.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			keys[DOWN] = false;
			if (!keys[UP])
				player->setDirectionY(0);
			else
				player->setDirectionY(1);
		}
		//left
		else if (events.keyboard.keycode == ALLEGRO_KEY_A || events.keyboard.keycode == ALLEGRO_KEY_LEFT) {
			keys[LEFT] = false;
			if (!keys[RIGHT])
				player->setDirectionX(0);
			else
				player->setDirectionX(1);
		}
		//right
		else if (events.keyboard.keycode == ALLEGRO_KEY_D || events.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
			keys[RIGHT] = false;
			if (!keys[LEFT])
				player->setDirectionX(0);
			else
				player->setDirectionX(-1);
		}
	}

	else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
		//up
		if (events.keyboard.keycode == ALLEGRO_KEY_W || events.keyboard.keycode == ALLEGRO_KEY_UP) {
			keys[UP] = true;
			player->setDirectionY(-1);
		}
		//down
		else if (events.keyboard.keycode == ALLEGRO_KEY_S || events.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			keys[DOWN] = true;
			player->setDirectionY(1);

		}
		//left
		else if (events.keyboard.keycode == ALLEGRO_KEY_A || events.keyboard.keycode == ALLEGRO_KEY_LEFT) {
			keys[LEFT] = true;
			player->setDirectionX(-1);

		}
		//right
		else if (events.keyboard.keycode == ALLEGRO_KEY_D || events.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
			keys[RIGHT] = true;
			player->setDirectionX(1);

		}

		else if (events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			endgame = true;
		
		//interact
		else if (events.keyboard.keycode == ALLEGRO_KEY_E) {

			int size = propArr->getSize();
			Prop* tmpProp = NULL;
			for (int i = 1; i < size; i++) {
				tmpProp = propArr->getElement(i);
				if (player->nearTo(tmpProp) && tmpProp->isInteractable() && tmpProp->isActive()) {
					tmpProp->interact();
					if (tmpProp->getType() == "pickUp") {
						//add to inventory
						inventory->add(new InvCell(tmpProp->getBitmap(),tmpProp->getName(),1));
					}
					//tmpProp->setCollidable(!tmpProp->isCollidable());
				}
			}
		}

		else if (events.keyboard.keycode == ALLEGRO_KEY_I) {
			drawInv = !drawInv;
		}
	}
}

//check collisions with player
void checkCollisions(Character* player) {
	int size = propArr->getSize();
	Prop* tmpProp = NULL;
	for (int i = 1; i < size; i++) {
		tmpProp = propArr->getElement(i);
		if (player->collideProp(tmpProp)) {
			//tmpProp->collide();
			break;
		}
	}
}

//move props
void transformProps(int dx, int dy) {
	int size = propArr->getSize();
	for (int i = 0; i < size; i++) {
		propArr->getElement(i)->transform(-dx, -dy);
	}
}

void printPositions() {
	std::cout << "Player: (" << player->getX() << ", " << player->getY()<<std::endl;
	int size = propArr->getSize();
	Prop* tmpProp = NULL;
	for (int i = 1; i < size; i++) {
		tmpProp = propArr->getElement(i);
		std::cout << tmpProp->getName()<<" (" << tmpProp->getX() << ", " << tmpProp->getY() << std::endl;
	}
}