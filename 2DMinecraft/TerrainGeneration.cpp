#include "2dMinecraft.h"
#include <iostream>

BlockIds** createTerrain(int seed)
{
	srand(seed);

	int dirtHeight = 0.5f * Settings::SCREEN_BLOCKS_HEIGHT;
	int grassHeight = 0.1f * Settings::SCREEN_BLOCKS_HEIGHT;
	int offset;
	BlockIds** blocks = new BlockIds*[Settings::SCREEN_BLOCKS_WIDTH];

	for (int x = 0; x < Settings::SCREEN_BLOCKS_WIDTH; x++)
	{
		offset = rand() % 3;
		blocks[x] = new BlockIds[Settings::SCREEN_BLOCKS_HEIGHT];

		for (int y = 0; y < Settings::SCREEN_BLOCKS_HEIGHT; y++)
		{
			if (y <= dirtHeight + offset)
			{
				blocks[x][y] = DIRT;
			}
			else if (y <= dirtHeight + grassHeight + offset)
			{
				blocks[x][y] = GRASS;
			}
			else
			{
				blocks[x][y] = AIR;
			}
		}
	}

	/*for (int y = 0; y < Settings::SCREEN_BLOCKS_HEIGHT; y++)
	{
		for (int x = 0; x < Settings::SCREEN_BLOCKS_WIDTH; x++)
		{
			std::cout << blocks[x][y] << " ";
		}
		std::cout << std::endl;
	}*/

	return blocks;
}

void createBlockVertices(BlockIds** blockIDs, GLfloat* vertices, GLfloat* colors, int* size)
{
	int count = 0;

	*size = Settings::SCREEN_BLOCKS_WIDTH * Settings::SCREEN_BLOCKS_HEIGHT * 6 * 4;

	float blockWidth = 2.0f / Settings::SCREEN_BLOCKS_WIDTH;
	float blockHeight = 2.0f / Settings::SCREEN_BLOCKS_HEIGHT;
	float movementX = Settings::SCREEN_BLOCKS_WIDTH * blockWidth / 2.0f;
	float movementY = Settings::SCREEN_BLOCKS_HEIGHT * blockHeight / 2.0f;

	GLfloat color[4];

	for (int y = 0; y < Settings::SCREEN_BLOCKS_HEIGHT; y++)
	{
		for (int x = 0; x < Settings::SCREEN_BLOCKS_WIDTH; x++)
		{
			//upper right
			vertices[0 + (count * 24)] = (blockWidth * (x + 1)) - 1.0f;
			vertices[1 + (count * 24)] = (blockHeight * (y + 1)) - 1.0f;
			vertices[2 + (count * 24)] = 0.0f;
			vertices[3 + (count * 24)] = 1.0f;

			//upper left
			vertices[4 + (count * 24)] = (blockWidth * (x)) - 1.0f;
			vertices[5 + (count * 24)] = (blockHeight * (y + 1)) - 1.0f;
			vertices[6 + (count * 24)] = 0.0f;
			vertices[7 + (count * 24)] = 1.0f;

			//down right
			vertices[8 + (count * 24)] = (blockWidth * (x + 1)) - 1.0f;
			vertices[9 + (count * 24)] = (blockHeight * (y)) - 1.0f;
			vertices[10 + (count * 24)] = 0.0f;
			vertices[11 + (count * 24)] = 1.0f;

			//upper left
			vertices[12 + (count * 24)] = (blockWidth * (x)) - 1.0f;
			vertices[13 + (count * 24)] = (blockHeight * (y + 1)) - 1.0f;
			vertices[14 + (count * 24)] = 0.0f;
			vertices[15 + (count * 24)] = 1.0f;

			//down left
			vertices[16 + (count * 24)] = (blockWidth * (x)) - 1.0f;
			vertices[17 + (count * 24)] = (blockHeight * (y)) - 1.0f;
			vertices[18 + (count * 24)] = 0.0f;
			vertices[19 + (count * 24)] = 1.0f;

			//down right
			vertices[20 + (count * 24)] = (blockWidth * (x + 1)) - 1.0f;
			vertices[21 + (count * 24)] = (blockHeight * (y)) - 1.0f;
			vertices[22 + (count * 24)] = 0.0f;
			vertices[23 + (count * 24)] = 1.0f;

			switch (blockIDs[x][y])
			{
			case (AIR):
				color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
				break;
			case (GRASS):
				color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; color[3] = 1.0f;
				break;
			case (DIRT):
				color[0] = 0.5f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
				break;
			default:
				color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
				break;
			}	

			//color[0] = 0.5f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;

			for (int i = 0; i < 6; i++) 
			{
				colors[(4 * i) + (count * 24) + 0] = color[0];
				colors[(4 * i) + (count * 24) + 1] = color[1];
				colors[(4 * i) + (count * 24) + 2] = color[2];
				colors[(4 * i) + (count * 24) + 3] = color[3];
			}

			count++;
		}
	}

	/*using namespace std;

	count = 0;
	
	for (int x = 0; x < *size / 4; x++) 
	{
		cout << vertices[(x * 4) + 0] << " " << vertices[(x * 4) + 1] << " " << vertices[(x * 4) + 2] << " " << vertices[(x * 4) + 3] << "    ";
		cout << colors[(x * 4) + 0] << " " << colors[(x * 4) + 1] << " " << colors[(x * 4) + 2] << " " << colors[(x * 4) + 3] << endl;
	}*/

	/*using namespace std;

	int blockCount = 0; 
	int verticeCount = 0;

	for (int x = 0; x < *size; x++)
	{
		cout << vertices[x] << " ";

		blockCount++;
		verticeCount++;

		if (verticeCount == 4)
		{
			cout << endl;
		}

		if (blockCount == 6)
		{
			cout << endl;
			blockCount = 0;
		}
	}*/
}