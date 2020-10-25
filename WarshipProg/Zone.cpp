#include "Zone.h"

void Zone::ChangeTo(size_t i, size_t j, Cell cellType) {
	zone[i][j] = cellType;
}