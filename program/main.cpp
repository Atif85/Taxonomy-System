#include "taxmanager.h"
#include "menu.h"

int main() {
    TaxManager taxManager;
    Menu menu(taxManager);

    menu.showMenu();  // Start the menu loop

    return 0;
}
