#include "widget_edt.h"

using namespace edt_mps;

creneau_widget::creneau_widget(QWidget * parent) : QWidget (parent) {
    m_heure_label = new QLabel(tr("Nombre d'heure"));
    m_heure_spin_box = new QSpinBox;
    m_heure_spin_box->setRange(1,Nbr_Heure);
    m_classe = new QCheckBox(tr("Par demie-classe"));
    m_semaine = new QCheckBox(tr("Une semaine sur deux"));
    m_main_Layout = new QHBoxLayout(this);
    m_main_Layout->addWidget(m_heure_label);
    m_main_Layout->addWidget(m_heure_spin_box);
    m_main_Layout->addWidget(m_classe);
    m_main_Layout->addWidget(m_semaine);
}

void creneau_widget::set_value(mps::flag code) {
    m_heure_spin_box->setValue(code & Heure_Creneau);
    m_classe->setChecked(code & Classe_Creneau);
    m_semaine->setChecked(code & Semaine_Creneau);
}

mps::flag creneau_widget::value() const {
    auto fl = static_cast<mps::flag::flag_type>(m_heure_spin_box->value());
    if(m_classe->isChecked())
        fl |= Classe_Creneau;
    if(m_semaine)
        fl |= Semaine_Creneau;
    return fl;
}

matiere_creneau_widget::matiere_creneau_widget(QWidget * parent) : creneau_widget (parent) {
    m_matiere_label = new QLabel(tr("Matière :"));
    m_matiere_edit = new QLineEdit;
}
