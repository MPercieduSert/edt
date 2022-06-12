#include "edt_tab.h"

using namespace edt_mps;

mps::fenetre::abstract_tab_module * edt_tab::create_tab(const tab_index& pair, const std::vector<QVariant> &args) const {
    if(pair.first < predef_tab::Nbr_Predef_Tab_Id)
        return predef_tab::create_tab(pair,args);
    else
        switch (pair.first) {
        case info_tab_edt::Classe_Tab_Id:
            return new classe_tab(bdd(),pair);
        case info_tab_edt::Prof_Tab_Id:
            return new prof_tab(bdd(),pair);
        default:
            return nullptr;
        }
}

abstract_edt_tab::abstract_edt_tab(bdd_edt & bd, tab_index pair, QWidget * parent)
    : abstract_tab_module_with_bdd(bd,pair,parent), m_prof(static_cast<idt>(pair.second)) {
    bdd().get(m_prof);
    m_matieres = bdd().get_list<matiere>(matiere::Id_Prof,m_prof.id(),matiere::Num);
    //nom
    m_nom_label = new QLabel;
    m_nom_edit = new QLineEdit;
    connect(m_nom_edit,&QLineEdit::textChanged,this,&abstract_tab_module::title_changed);
//    connect(m_nom_edit,&QLineEdit::textChanged,this,[this]{
//        auto * tab = static_cast<QTabWidget *>(this->parent());
//        if(tab)
//            tab->setTabText(tab->currentIndex(),m_nom_edit->text());});
    m_nom_layout = new QHBoxLayout;
    m_nom_layout->addWidget(m_nom_label);
    m_nom_layout->addWidget(m_nom_edit);
    m_horaire_layout = new QVBoxLayout;
    m_horaire_layout->addLayout(m_nom_layout);

    m_creneau_view = new mps::widget::node_view(std::make_unique<mps::widget::rounded_arc_painter>());
    m_creneau_model = new matiere_creneau_model(static_cast<idt>(pair.second), static_cast<bdd_edt &>(bd),this);
    m_creneau_view->set_model(m_creneau_model);
    m_creneau_view->set_delegate(new mps::delegate::standard_node_delegate(this));

    m_main_layout = new QHBoxLayout(this);
    m_main_layout->addLayout(m_horaire_layout);
    m_main_layout->addWidget(m_creneau_view);
}

void abstract_edt_tab::add_bouton(QPushButton * bouton, szt indice){
    bouton->setText(model_tableau_edt::options.at(indice).text);
    auto pal = bouton->palette();
    pal.setColor(QPalette::Button,model_tableau_edt::options.at(indice).color);
    bouton->setPalette(pal);
    m_bouton_layout->addWidget(bouton);
}

void abstract_edt_tab::add_boutons(){
    m_bouton_layout = new QHBoxLayout;
    m_libre_bouton = new QPushButton;
    add_bouton(m_libre_bouton,model_tableau_edt::Libre);
    m_interdit_bouton = new QPushButton;
    add_bouton(m_interdit_bouton,model_tableau_edt::Interdit);
    m_horaire_layout->addLayout(m_bouton_layout);
}

classe_tab::classe_tab(bdd_edt & bdd, tab_index pair, QWidget * parent)
    : abstract_edt_tab (bdd,pair,parent) {
    m_nom_label->setText(tr("Nom de la classe :"));
    m_nom_edit->setText(m_matieres.front().nom());
    creneau cr(id_matiere(),Num_Nbr_Heure);
    m_bdd.get_unique(cr);
    m_model = new model_tableau_edt(bdd,id_matiere(),static_cast<int>(cr.code().value()),this);
    m_view = new QTableView;
    m_view->setModel(m_model);
    m_horaire_layout->addWidget(m_view);
    add_boutons();
    connect(m_libre_bouton,&QPushButton::clicked,this,
            [this]{m_model->change_value_selection(m_view->selectionModel(),Libre_Code);});
    connect(m_interdit_bouton,&QPushButton::clicked,this,
            [this]{m_model->change_value_selection(m_view->selectionModel(),Interdit_Code);});
}

void classe_tab::sauver() {
    m_matieres.front().set_nom(m_nom_edit->text());
    m_bdd.save(m_matieres);
    m_model->sauver();
}

prof_tab::prof_tab(bdd_edt & bdd, tab_index pair, QWidget * parent)
    : abstract_edt_tab (bdd,pair,parent) {
    m_nom_label->setText(tr("Nom de l'enseignant :"));
    m_nom_edit->setText(m_prof.nom());
}
