#include <GL3\gl3w.h>
#include <random>

namespace Settings 
{
	const int SCREEN_SIZE_WIDTH = 400;
	const int SCREEN_SIZE_HEIGHT = 400;
	const int SCREEN_BLOCKS_WIDTH = 40;
	const int SCREEN_BLOCKS_HEIGHT = 40;
}

enum BlockIds {AIR = 0, GRASS = 1, DIRT = 2};

void createBlockVertices(BlockIds** blockIDs, GLfloat* vertices, GLfloat* colors, int* size); //takes in a empty GLfloat array and a array of block ids and
														//creates the vertices for all of the blocks and the colors
BlockIds** createTerrain(int seed);