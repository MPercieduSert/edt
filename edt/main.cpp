#include <QApplication>

#include "fen_principale_edt.h"

int main(int argc, char *argv[]) {
    using namespace edt_mps;
    QApplication a(argc, argv);
    auto bdd = std::make_unique<bdd_edt>();
    auto *zone_centrale = new mps::fenetre::predef_zone_centrale(new edt_tab(*bdd, nullptr));
    fen_principale_edt fen(new noyau_edt,std::move(bdd),zone_centrale);
    fen.show();
    return a.exec();
}
