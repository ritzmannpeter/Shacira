/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [xml_int.h]                Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef xml_int_INCL
#define xml_int_INCL


#include "ptm.h"
#include "gls.h"


#ifdef __cplusplus
extern "C" {
#endif


/* --------------------- symbol objects - init & quit --------------------- */

void xml_initSymbols();                /*                                   */
void xml_quitSymbols();                /*                                   */

/* -------------------------- Types & Constants --------------------------- */

AbstractType( xml );

AbstractType( xmlXDoc );
AbstractType( xmlXDecl );
AbstractType( xmlWhite );
AbstractType( xmlEDecl );
AbstractType( xmlEBody );
AbstractType( xmlAttr );
AbstractType( xmlCDecl );

/* --------------------------- Access to Tokens --------------------------- */

c_bool Txml_DCharRef(GLS_Tok x);       /*                                   */
c_bool Txml_HCharRef(GLS_Tok x);       /*                                   */
c_bool Txml_ERef(GLS_Tok x);           /*                                   */
c_bool Txml_PERef(GLS_Tok x);          /*                                   */
c_bool Txml_Nmtoken(GLS_Tok x);        /*                                   */
c_bool Txml_XMLDecl(GLS_Tok x);        /*                                   */
c_bool Txml_PI(GLS_Tok x);             /*                                   */
c_bool Txml_CDSect(GLS_Tok x);         /*                                   */
c_bool Txml_XMLOpr(GLS_Tok x);         /*                                   */
c_bool Txml_Name(GLS_Tok x);           /*                                   */
c_bool Txml_dtdEmbed(GLS_Tok x);       /*                                   */
c_bool Txml_DTDStart(GLS_Tok x);       /*                                   */
c_bool Txml_Literal(GLS_Tok x);        /*                                   */
c_bool Txml_CharData(GLS_Tok x);       /*                                   */
c_bool Txml_Empty(GLS_Tok x);          /*                                   */
c_bool Txml_Comment(GLS_Tok x);        /*                                   */
c_bool Txml__other_(GLS_Tok x);        /*                                   */

/* --------------------------- Access to Terms ---------------------------- */

c_bool xml_xml(PT_Term x, xml* x1);        /*                               */
c_bool xml_XDoc(PT_Term x, xmlXDoc* x1);   /*                               */
c_bool xml_XDecl(PT_Term x, xmlXDecl* x1); /*                               */
c_bool xml_White(PT_Term x, xmlWhite* x1); /*                               */
c_bool xml_EDecl(PT_Term x, xmlEDecl* x1); /*                               */
c_bool xml_EBody(PT_Term x, xmlEBody* x1); /*                               */
c_bool xml_Attr(PT_Term x, xmlAttr* x1);   /*                               */
c_bool xml_CDecl(PT_Term x, xmlCDecl* x1); /*                               */

/* --------------------------------- xml ---------------------------------- */

c_bool xml_Start_XDoc(xml x, xmlXDoc* x1)
#define xml_Start_0   xml_Start_XDoc
;


/* --------------------------------- XDoc --------------------------------- */

c_bool xmlXDoc_dfn(xmlXDoc x, xmlXDecl* x1, GLS_Lst(xmlCDecl)* x2); /*      */

/* -------------------------------- XDecl --------------------------------- */

c_bool xmlXDecl_nul(xmlXDecl x);              /*                            */
c_bool xmlXDecl_dfn(xmlXDecl x, GLS_Tok* x1); /*                            */

/* -------------------------------- White --------------------------------- */

c_bool xmlWhite_nul(xmlWhite x);              /*                            */
c_bool xmlWhite_spc(xmlWhite x, GLS_Tok* x1); /*                            */

/* -------------------------------- EDecl --------------------------------- */

c_bool xmlEDecl_dfn(xmlEDecl x, GLS_Tok* x1, GLS_Lst(xmlAttr)* x2,
                    xmlEBody* x3)
;


/* -------------------------------- EBody --------------------------------- */

c_bool xmlEBody_dfn(xmlEBody x, GLS_Lst(xmlCDecl)* x1, GLS_Tok* x2,
                    xmlWhite* x3)
;

c_bool xmlEBody_nul(xmlEBody x);       /*                                   */

/* --------------------------------- Attr --------------------------------- */

c_bool xmlAttr_spc(xmlAttr x, xmlWhite* x1); /*                             */

c_bool xmlAttr_dfn(xmlAttr x, xmlWhite* x1, GLS_Tok* x2,
                   xmlWhite* x3, xmlWhite* x4,
                   GLS_Tok* x5)
;


/* -------------------------------- CDecl --------------------------------- */

c_bool xmlCDecl_eref(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_data(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_nmtk(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_cref(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_sect(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_xcom(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_xopr(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_pref(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_name(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_pi(xmlCDecl x, GLS_Tok* x1);               /*               */
c_bool xmlCDecl_elm(xmlCDecl x, xmlEDecl* x1);             /*               */
c_bool xmlCDecl_etg0(xmlCDecl x);                          /*               */
c_bool xmlCDecl_lit(xmlCDecl x, GLS_Tok* x1);              /*               */
c_bool xmlCDecl_else(xmlCDecl x, GLS_Tok* x1);             /*               */
c_bool xmlCDecl_etg1(xmlCDecl x);                          /*               */
c_bool xmlCDecl_typ(xmlCDecl x, GLS_Tok* x1, GLS_Tok* x2); /*               */
c_bool xmlCDecl_spc(xmlCDecl x, xmlWhite* x1);             /*               */
c_bool xmlCDecl_eq(xmlCDecl x);                            /*               */
c_bool xmlCDecl_href(xmlCDecl x, GLS_Tok* x1);             /*               */


#ifdef __cplusplus
}
#endif

#endif
