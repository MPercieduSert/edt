#include "noyau_edt.h"

using namespace edt_mps;

void noyau_edt::set_config_by_path(const QString &config_path, QWidget *modal_parent)
    {set_config(std::make_unique<config_edt>(config_path), modal_parent);}
