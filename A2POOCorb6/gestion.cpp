#include "gestion.h"
#include"PERSONNEL.h"
#include"ADRESSE.h"
#include"PRODUITS.h"
#include "NATURE.h"
#include"MODE_REGLEMENT.h"
#include"COULEUR.h"
#include"PAIEMENT.h"
#include"COMMANDES.h"
namespace NS_Svc
{
	gestion::gestion(void)
	{
		this->cad = gcnew NS_Composants::CL_CAD();
		this->adresse = gcnew NS_Composants::ADRESSE();
		this->client = gcnew NS_Composants::CLIENT();
		this->personnel = gcnew NS_Composants::PERSONNEL();
		this->commande = gcnew NS_Composants::COMMANDES();
		this->tarif = gcnew NS_Composants::TARIF();
		this->produit = gcnew NS_Composants::PRODUITS();
		//this->reglement = gcnew NS_Composants::MODE_REGLEMENT();
		this->reglement = gcnew NS_Composants::MODE_REGLEMENTS();
		this->contenir = gcnew NS_Composants::CONTENIR();
		this->paiement = gcnew NS_Composants::PAIEMENT();
		this->nature = gcnew NS_Composants::NATURE();

		this->ds = gcnew Data::DataSet();
	}
	DataSet^ gestion::listeClient(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->client->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listePersonnel(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->personnel->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listePersonnelAdresse(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->personnel->SELECTPERSONNELADRESSE(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listeAdresse(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->adresse->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listeCommande(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->commande->SELECT(), dataTableName);
		return this->ds;
	}

	DataSet^ gestion::listeClientAdresse(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->client->SELECTCLIENTADRESSE(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listeReglement(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->reglement->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listePaiement(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->paiement->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listeCouleur(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->couleur->SELECT(), dataTableName);
		return this->ds;
	}
	DataSet^ gestion::listeTarif(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->tarif->SELECT(), dataTableName);
		return this->ds;
	}

	DataSet^ gestion::listeProduits(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->produit->SELECT(), dataTableName);
		return this->ds;
	}

	DataSet^ gestion::listeProdNatTar(String^ dataTableName)
	{
		this->ds->Clear();
		this->ds = this->cad->getRows(this->produit->SELECTProdNatTar(), dataTableName);
		return this->ds;
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////


	int gestion::ajouterClient(String^ NOM_CLIENT, String^ PRENOM_CLIENT, String^ DATE_NAISSANCE_CLIENT, String^ DATE_PREMIERE_COMMANDE_CLIENT, String^ RUE_FAC, int CODE_POSTAL_FAC, String^ VILLE_FAC, String^ RUE_LIV, int CODE_POSTAL_LIV, String^ VILLE_LIV)
	{
		int id_personne;
		this->client->setNOM_CLIENT(NOM_CLIENT);
		this->client->setPRENOM_CLIENT(PRENOM_CLIENT);
		this->client->setDATE_NAISSANCE_CLIENT(DATE_NAISSANCE_CLIENT);
		this->client->setDATE_PREMIERE_COMMANDE_CLIENT(DATE_PREMIERE_COMMANDE_CLIENT);
		id_personne = this->cad->actionRowsID(this->client->INSERT());

		if (RUE_FAC != RUE_LIV || CODE_POSTAL_FAC != CODE_POSTAL_LIV || VILLE_FAC != VILLE_LIV) {
			this->adresse->setID_CLIENT_FAC(id_personne);
			this->adresse->setRUE(RUE_FAC);
			this->adresse->setCODE_POSTAL(CODE_POSTAL_FAC);
			this->adresse->setVILLE(VILLE_FAC);
			this->cad->actionRowsID(this->adresse->INSERT_FAC());

			this->adresse->setID_CLIENT_LIV(id_personne);
			this->adresse->setRUE(RUE_LIV);
			this->adresse->setCODE_POSTAL(CODE_POSTAL_LIV);
			this->adresse->setVILLE(VILLE_LIV);
			this->cad->actionRowsID(this->adresse->INSERT_LIV());
		}
		else {
			this->adresse->setID_CLIENT_FAC(id_personne);
			this->adresse->setID_CLIENT_LIV(id_personne);
			this->adresse->setRUE(RUE_FAC);
			this->adresse->setCODE_POSTAL(CODE_POSTAL_FAC);
			this->adresse->setVILLE(VILLE_FAC);
			this->cad->actionRowsID(this->adresse->INSERT_FAC_LIV());
		}

		return id_personne;
	}
	void gestion::modifierClient(int ID_CLIENT, String^ NOM_CLIENT, String^ PRENOM_CLIENT, String^ DATE_NAISSANCE_CLIENT, String^ DATE_PREMIERE_COMMANDE_CLIENT)
	{
		this->client->setID(ID_CLIENT);
		this->client->setNOM_CLIENT(NOM_CLIENT);
		this->client->setPRENOM_CLIENT(PRENOM_CLIENT);
		this->client->setDATE_NAISSANCE_CLIENT(DATE_NAISSANCE_CLIENT);
		this->client->setDATE_PREMIERE_COMMANDE_CLIENT(DATE_PREMIERE_COMMANDE_CLIENT);
		this->cad->actionRows(this->client->UPDATE());
	}
	void gestion::supprimerClient(int ID_CLIENT)
	{
		this->client->setID(ID_CLIENT);
		this->cad->actionRows(this->client->DELETE());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	int gestion::ajouterPersonnel(int ID_SUP, String^ NOM_PERSONNEL, String^ PRENOM_PERSONNEL, String^ ADRESSE_MAIL_PERSONNEL, String^ DATE_EMBAUCHE, String^ RUE, int CODE_POSTAL, String^ VILLE)
	{
		int id_personnel;
		int id_adresse;
		this->adresse->setRUE(RUE);
		this->adresse->setCODE_POSTAL(CODE_POSTAL);
		this->adresse->setVILLE(VILLE);
		id_adresse = this->cad->actionRowsID(this->adresse->INSERT());

		this->personnel->setID_ADRESSE(id_adresse);
		this->personnel->setID_SUP(ID_SUP);
		this->personnel->setNOM_PERSONNEL(NOM_PERSONNEL);
		this->personnel->setPRENOM_PERSONNEL(PRENOM_PERSONNEL);
		this->personnel->setADRESSE_MAIL_PERSONNEL(ADRESSE_MAIL_PERSONNEL);
		this->personnel->setDATE_EMBAUCHE(DATE_EMBAUCHE);
		id_personnel = this->cad->actionRowsID(this->personnel->INSERT());
		return id_personnel;
	}
	void gestion::modifierPersonnel(int ID_PERSONNEL, String^ NOM_PERSONNEL, String^ PRENOM_PERSONNEL, String^ ADRESSE_MAIL_PERSONNEL, String^ DATE_EMBAUCHE)
	{
		this->personnel->setID_PERSONNEL(ID_PERSONNEL);
		this->personnel->setNOM_PERSONNEL(NOM_PERSONNEL);
		this->personnel->setPRENOM_PERSONNEL(PRENOM_PERSONNEL);
		this->personnel->setADRESSE_MAIL_PERSONNEL(ADRESSE_MAIL_PERSONNEL);
		this->personnel->setDATE_EMBAUCHE(DATE_EMBAUCHE);
		this->cad->actionRows(this->personnel->UPDATE());
	}
	void gestion::supprimerPersonnel(int ID_PERSONNEL)
	{
		this->personnel->setID_PERSONNEL(ID_PERSONNEL);
		this->cad->actionRows(this->personnel->DELETE());
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterAdresse(String^ RUE, int CODE_POSTAL, String^ VILLE)
	{
		int id_adresse;
		this->adresse->setRUE(RUE);
		this->adresse->setCODE_POSTAL(CODE_POSTAL);
		this->adresse->setVILLE(VILLE);
		id_adresse = this->cad->actionRowsID(this->adresse->INSERT());
		return id_adresse;
	}
	void gestion::modifierAdresse(int ID_ADRESSE, String^ RUE, int CODE_POSTAL, String^ VILLE)
	{
		this->adresse->setID_ADRESSE(ID_ADRESSE);
		this->adresse->setRUE(RUE);
		this->adresse->setCODE_POSTAL(CODE_POSTAL);
		this->adresse->setVILLE(VILLE);
		this->cad->actionRows(this->adresse->UPDATE());
	}
	void gestion::supprimerAdresse(int ID_ADRESSE)
	{
		this->adresse->setID_ADRESSE(ID_ADRESSE);
		this->cad->actionRows(this->adresse->DELETE());
	}
	void gestion::supprimerAdresseClient(int ID_CLIENT)
	{
		this->adresse->setID_CLIENT_FAC(ID_CLIENT);
		this->adresse->setID_CLIENT_LIV(ID_CLIENT);

		this->cad->actionRows(this->adresse->DELETEAdresseClient());
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	int gestion::ajouterCommande(String^ REF_COMMANDE, String^ DATE_LIVRAISON_PREVUE, String^ DATE_EMISSION_COMMANDE, String^ DATE_SOLDE_REGLEMENT, int MONTANT_HT, int MONTANT_TVA, int MONTANT_TTC, String^ DATE_EMISSION_FACTURE, int MONTANT_PAIEMENT, String^ DATE_PAIEMENT, String^ MODE_REGLEMENT, int QUANTITE_ARTICLE)
	{
		int id_commande;
		this->commande->setREF_COMMANDE(REF_COMMANDE);
		this->commande->setID_CLIENTC(id_commande);
		this->paiement->setID_PAIEMENT(id_commande);
		this->paiement->setID_MODEP(id_commande);
		this->reglement->setID_MODE(id_commande);
		this->commande->setDATE_LIVRAISON_PREVUE(DATE_LIVRAISON_PREVUE);
		this->commande->setDATE_EMISSION_COMMANDE(DATE_EMISSION_COMMANDE);
		this->commande->setDATE_SOLDE_REGLEMENT(DATE_SOLDE_REGLEMENT);
		this->commande->setMONTANT_HT(MONTANT_HT);
		this->commande->setMONTANT_TVA(MONTANT_TVA);
		this->commande->setMONTANT_TTC(MONTANT_TTC);
		this->commande->setDATE_EMISSION_FACTURE(DATE_EMISSION_FACTURE);
		id_commande = this->cad->actionRowsID(this->commande->INSERT());
		this->paiement->setMONTANT_PAIEMENT(MONTANT_PAIEMENT);
		this->paiement->setDATE_PAIEMENT(DATE_PAIEMENT);
		this->reglement->setMODE_REGLEMENT(MODE_REGLEMENT);
		this->contenir->setQUANTITE_ARTICLE(QUANTITE_ARTICLE);
		
	
		this->cad->actionRowsID(this->paiement->INSERT());
		this->cad->actionRowsID(this->reglement->INSERT());
		this->cad->actionRowsID(this->contenir->INSERT());
		return id_commande;

		
			
	}
	

	void gestion::supprimerCommande(String^ REF_COMMANDE)
	{
		this->commande->setREF_COMMANDE(REF_COMMANDE);
		this->cad->actionRows(this->commande->DELETE());
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void gestion::ajouterProduit(String^ REF_PRODUIT, int ID_NATURE, int ID_TARIF, String^ PRIX_HT, String^ DESIGNATION, int QUANTITE_STOCK, int SEUIL_REAPPROVISIONNEMENT, String^ TAUX_TVA)
	{
		this->produit->setREF_PRODUIT(REF_PRODUIT);
		this->produit->setID_NAT(ID_NATURE);
		this->produit->setID_TARIF(ID_TARIF);
		this->produit->setPRIX_HT(PRIX_HT);
		this->produit->setDESIGNATION(DESIGNATION);
		this->produit->setQUANTITE_STOCK(QUANTITE_STOCK);
		this->produit->setSEUIL_REAPPROVISIONNEMENT(SEUIL_REAPPROVISIONNEMENT);
		this->produit->setTAUX_TVA(TAUX_TVA);
	}
	void gestion::ajouterProdNatTar(String^ REF_PRODUIT, String^ PRIX_HT, String^ DESIGNATION, int QUANTITE_STOCK, int SEUIL_REAPPROVISIONNEMENT, String^ TAUX_TVA, int ID_NATURE, String^ INTITULE_NATURE, int ID_TARIF, String^ PRIX_UNITAIRE, String^ INTITULE_TARIF)
	{
		this->produit->setREF_PRODUIT(REF_PRODUIT);
		this->produit->setPRIX_HT(PRIX_HT);
		this->produit->setDESIGNATION(DESIGNATION);
		this->produit->setQUANTITE_STOCK(QUANTITE_STOCK);
		this->produit->setSEUIL_REAPPROVISIONNEMENT(SEUIL_REAPPROVISIONNEMENT);
		this->produit->setTAUX_TVA(TAUX_TVA);
		this->produit->setID_NAT(ID_NATURE);
		this->produit->setID_TARIF(ID_TARIF);
		this->cad->actionRows(this->produit->INSERT());

		this->nature->setID_NATURE(ID_NATURE);
		this->nature->setINTITULE_NATURE(INTITULE_NATURE);
		this->cad->actionRows(this->nature->INSERT());

		this->tarif->setID_TARIF(ID_TARIF);
		this->tarif->setID_NATURE(ID_NATURE);
		this->tarif->setREF_PRODUIT(REF_PRODUIT);
		this->tarif->setPRIX_UNITAIRE(PRIX_UNITAIRE);
		this->tarif->setINTITULE_TARIF(INTITULE_TARIF);
		this->cad->actionRows(this->tarif->INSERT());
	}
	void gestion::modifierProduit(String^ REF_PRODUIT, int ID_NATURE, int ID_TARIF, String^ PRIX_HT, String^ DESIGNATION, int QUANTITE_STOCK, int SEUIL_REAPPROVISIONNEMENT, String^ TAUX_TVA)
	{
		this->produit->setREF_PRODUIT(REF_PRODUIT);
		this->produit->setPRIX_HT(PRIX_HT);
		this->produit->setDESIGNATION(DESIGNATION);
		this->produit->setQUANTITE_STOCK(QUANTITE_STOCK);
		this->produit->setSEUIL_REAPPROVISIONNEMENT(SEUIL_REAPPROVISIONNEMENT);
		this->produit->setTAUX_TVA(TAUX_TVA);
		this->cad->actionRows(this->produit->UPDATE());
	}
	void gestion::supprimerProduit(String^ REF_PRODUIT)
	{
		this->produit->setREF_PRODUIT(REF_PRODUIT);
		this->cad->actionRows(this->produit->DELETE());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterNature(String^ INTITULE_NATURE)
	{
		int id_nature;
		this->nature->setINTITULE_NATURE(INTITULE_NATURE);
		id_nature = this->cad->actionRowsID(this->nature->INSERT());
		return id_nature;
	}
	void gestion::modifierNature(int ID_NATURE, String^ INTITULE_NATURE)
	{
		this->nature->setID_NATURE(ID_NATURE);
		this->nature->setINTITULE_NATURE(INTITULE_NATURE);
		this->cad->actionRows(this->nature->UPDATE());
	}
	void gestion::supprimerNature(int ID_NATURE)
	{
		this->nature->setID_NATURE(ID_NATURE);
		this->cad->actionRows(this->nature->DELETE());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterMode(String^ MODE_REGLEMENT)
	{
		int id_reglement;
		this->reglement->setMODE_REGLEMENT(MODE_REGLEMENT);
		id_reglement = this->cad->actionRowsID(this->reglement->INSERT());
		return id_reglement;
	}
	void gestion::modifierMode(int ID_MODE, String^ MODE_REGLEMENT)
	{
		this->reglement->setID_MODE(ID_MODE);
		this->reglement->setMODE_REGLEMENT(MODE_REGLEMENT);
		this->cad->actionRows(this->reglement->UPDATE());

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterCouleur(String^ NOM_COULEUR)
	{
		int id_couleur;
		this->couleur->setNOM_COULEUR(NOM_COULEUR);
		id_couleur = this->cad->actionRowsID(this->couleur->INSERT());
		return id_couleur;
	}
	void gestion::modifierCouleur(int ID_COULEUR, String^ NOM_COULEUR)
	{
		this->couleur->setID_COULEUR(ID_COULEUR);
		this->couleur->setNOM_COULEUR(NOM_COULEUR);
		this->cad->actionRows(this->couleur->UPDATE());

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterPaiement(String^ DATE_PAIEMENT, String^ MONTANT_PAIEMENT)
	{
		int id_paiement;
		this->paiement->setDATE_PAIEMENT(DATE_PAIEMENT);
		id_paiement = this->cad->actionRowsID(this->paiement->INSERT());
		return id_paiement;
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int gestion::ajouterTarif(String^ INTITULE_TARIF)
	{
		int id_tarif;
		this->tarif->setINTITULE_TARIF(INTITULE_TARIF);
		id_tarif = this->cad->actionRowsID(this->tarif->INSERT());
		return id_tarif;
	}
	void gestion::modifierTarif(int ID_TARIF, String^ INTITULE_TARIF)
	{
		this->tarif->setID_TARIF(ID_TARIF);
		this->tarif->setINTITULE_TARIF(INTITULE_TARIF);
		this->cad->actionRows(this->tarif->UPDATE());
	}
	void gestion::supprimerTarif(int ID_TARIF)
	{
		this->tarif->setID_TARIF(ID_TARIF);
		this->cad->actionRows(this->tarif->DELETE());
	}



}