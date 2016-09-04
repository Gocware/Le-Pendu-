#ifndef EDITORINTERFATA_H
#define EDITORINTERFATA_H
#include<Sistem_Baza.h>
#include<Buton.h>
class EditorInterfata
{
    public:
        static void edit_ResetParamButon();
        static void edit_ResetParamImagine();
        static void edit_adaugaButon();
        static void edit_adaugaImagine();
        static void edit_desButoane();
        static void edit_desImagini();
        static void edit_stergeButon();
        static void edit_stergeImagine();
        static bool edit_contineMouse();
        static void edit_misca_MouseObiect();
        static void edit_Buton();
        static void edit_Img();
        static void des_PanouComanda();
        static void get_Comanda();
        //static void deseneazaCursor();
     private:
        static bool bt_TipButon,bt_mesajButon,bt_idButon,bt_textButon,bt_imgButon,bt_dimCaract,bt_x,bt_y;
        static bool img_pth,img_dim,img_x,img_y;
        static unsigned obj_selectat;

};

#endif // EDITORINTERFATA_H
