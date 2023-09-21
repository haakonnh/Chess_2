#include "ChessWindow.h"
#include <vector>



int main() {
    std::vector<int> ok(10);

    ChessWindow chess2;
    chess2.play();
    chess2.wait_for_close();
    return 0;
}

