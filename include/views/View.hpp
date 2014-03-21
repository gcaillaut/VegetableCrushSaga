#ifndef INCLUDED_VIEW_H
#define INCLUDED_VIEW_H

class Controller;

///
/// \brief Vue de base
///
class View
{
public:
	View (Controller *controller);
	virtual ~View () = 0;

	///
	/// \brief Efface l'écran
	///
	virtual void clear () = 0;

	///
	/// \brief Dessine les objets de la vue
	///
	virtual void draw () = 0;

	///
	/// \brief Affiche tout ce qui a été dessiné sur l'écran
	///
	virtual void display () = 0;

	///
	/// \brief Gère les évènements et les envoie au contrôleur
	///
	virtual void sendEvents () = 0;

	///
	/// \brief Boucle d'affichage de la vue
	///
	virtual void loop () = 0;

	///
	/// \brief Teste si la vue est démarrée
	/// \return Oui/Non
	///
	bool isRunning() const;

	///
	/// \brief Active la vue
	///
	void activate ();

	///
	/// \brief Désactive la vue
	///
	void deactivate ();

protected:
	Controller *controller;
	bool running;
};



#endif /* INCLUDED_VIEW_H */
