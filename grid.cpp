#include "grid.h"

Grid::Grid()
{
    memset(_data, 0, sizeof(int) * GRID_SIZE);
}

void Grid::draw(Arduboy& adb, const unsigned at_x, const unsigned at_y)
{
    const int16_t frame_width = 1;

    int16_t x_offset = at_x + frame_width;
    int16_t y_offset = at_y + frame_width;

    for (unsigned int y = 0; y < height(); y++) {
        for (unsigned int x = 0; x < width(); x++) {
            if (at(x, y) == 1) {
                adb.fillRect(x_offset, y_offset, SHAPE_BLOCK_WIDTH, SHAPE_BLOCK_WIDTH, BLACK);
            }

            x_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        }

        y_offset += SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING;
        x_offset = at_x + frame_width;
    }

    // Frame
    adb.drawRect(at_x, at_y,
        width()  * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        height() * (SHAPE_BLOCK_WIDTH + SHAPE_BLOCK_PADDING) + 1,
        BLACK
    );
}

void Grid::copy(Grid &other_grid)
{
    memcpy(_data, other_grid._data, sizeof(int) * GRID_SIZE);
}

void Grid::commit_actor(const shape_actor_t& actor)
{
    tetromino_t *tetromino = actor.tetromino;

    int width = 4;
    int height = 4;

    // Rotate if necessary
    int block[16] = { 0 };
    tetromino->rotated_shape_data(actor.rotation, &block);

    // Blit to grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (block[4 * y + x]) {
                set(actor.position.x + x, actor.position.y + y, 1);
            }
        }
    }
}

bool Grid::actor_collides(const shape_actor_t& actor)
{
    // todo
    return false;
}

bool Grid::actor_in_vert_bounds(const shape_actor_t& actor)
{
    // Currently not concerned with this.
    // if (actor.position.y < 0) return false;

    if (actor.position.y + actor.tetromino->height > height()) return false;

    return true;
}

bool Grid::actor_in_horiz_bounds(const shape_actor_t& actor)
{
    if (actor.position.x < 0) return false;
    if (actor.position.x + actor.tetromino->width > width()) return false;

    return true;
}
