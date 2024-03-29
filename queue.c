// File storing the orders that are currently recived.
//
// 2015, Matias Christensen & Mikael Kvalvær

#include "queue.h"
#include <assert.h>

// Array containing the order status of all floors and directions
static int orderArray[2][3] = {{0}};
/*
	[0][0] - floor 0 up
	[0][1] - floor 1 up
	[0][2] - floor 2 up
	[1][0] - floor 1 down
	[1][1] - floor 2 down
	[1][2] - floor 3 down
*/


// *** Internal function decleration ***

static int hasOrderAbove(int floor);
static int hasOrderBelow(int floor);
static void asertInput(int floor, order_direction_t dir);

// ***External functions implementation ***

void queue_addOrder(int floor, order_direction_t dir) {
	asertInput(floor, dir);

	switch (dir) {
		case ORDER_DIR_DOWN:
			orderArray[1][floor-1] = 1;
			break;
		case ORDER_DIR_UP:
			orderArray[0][floor] = 1;
			break;
		case ORDER_DIR_BOTH:
			if (floor >= 1) { orderArray[1][floor-1] = 1; }
			if (floor <= 2) { orderArray[0][floor]   = 1; }
			break;
	}
}

int queue_hasOrder(int floor, order_direction_t dir) {
	asertInput(floor, dir);

	switch (dir) {
		case ORDER_DIR_DOWN:
			return orderArray[1][floor-1];
		case ORDER_DIR_UP:
			return orderArray[0][floor];
		case ORDER_DIR_BOTH:
			if      (floor == 0) { return orderArray[0][0]; }
			else if (floor == 3) { return orderArray[1][2]; }
			else                 { return orderArray[0][floor] + orderArray[1][floor-1]; }
	}
}

int queue_hasOrderInDir(int floor, order_direction_t dir) {
	if (dir == ORDER_DIR_UP) {
		return hasOrderAbove(floor);
	} else {
		return hasOrderBelow(floor);
	}
}

void queue_clearOrder(int floor, order_direction_t dir) {
	asertInput(floor, dir);

	switch (dir) {
		case ORDER_DIR_DOWN:
			orderArray[1][floor-1] = 0;
			break;
		case ORDER_DIR_UP:
			orderArray[0][floor] = 0;
			break;
		case ORDER_DIR_BOTH:
			if (floor >= 1) { orderArray[1][floor-1] = 0; }
			if (floor <= 2) { orderArray[0][floor]   = 0; }
			break;
	}
}

void queue_clearAllOrders() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			orderArray[i][j] = 0;
		}
	}
}

// *** Internal function implementation ***

static int hasOrderAbove(int floor) {
	for (int i = floor+1; i < 4; ++i) {
		if (queue_hasOrder(i, ORDER_DIR_BOTH)) {
			return 1;
		}
	}
	return 0;
}

static int hasOrderBelow(int floor) {
	for (int i = floor-1; i >= 0; --i) {
		if (queue_hasOrder(i, ORDER_DIR_BOTH)) {
			return 1;
		}
	}
	return 0;
}

static void asertInput(int floor, order_direction_t dir) {
	assert(!(dir == ORDER_DIR_UP && (floor < 0 || floor > 2)));
	assert(!(dir == ORDER_DIR_DOWN && (floor < 1 || floor > 3)));
	assert(!(dir == ORDER_DIR_BOTH && (floor < 0 || floor > 3)));
}
