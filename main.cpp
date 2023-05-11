#include "ChessWindow.h"
#include "Board.h"

/* Chess 2 - the worlds best game. */

int main() {
    ChessWindow chess2;
    chess2.play();
    chess2.wait_for_close();
    return 0;
}

