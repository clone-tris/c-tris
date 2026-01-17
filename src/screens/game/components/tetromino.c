#include "screens/game/components/shape.h"

Shape randomTetromino() {
  return (Shape){.row = 0, .column = 0, .width = 0, .height = 0, .squares = {}};
}
