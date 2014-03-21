#ifndef INCLUDED_CONTROLLER_H
#define INCLUDED_CONTROLLER_H

class View;

///
/// \brief Contrôleur de base
///
class Controller
{
public:
  Controller ();
  virtual ~Controller () = 0;

  ///
  /// \brief Lorsqu'un clic est détecté
  /// \param x Position x
  /// \param y Position y
  ///
  virtual void onClick (const float x, const float y) = 0;

  ///
  /// \brief Lorsqu'un relâchement de clic est détecté
  /// \param x Position x
  /// \param y Position y
  ///
  virtual void onClickRelease (const float x, const float y) = 0;

  ///
  /// \brief Lorsque le focus de la fenêtre est perdu
  ///
  virtual void onLostFocus () = 0;

  ///
  /// \brief Lorsque le focus de la fenêtre est obtenu
  ///
  virtual void onGainedFocus () = 0;

  ///
  /// \brief Affecte la vue 'view' au contrôleur
  /// \param view Vue
  ///
  void setView (View *view);

private:
  View *current_view;
};


#endif /* INCLUDED_CONTROLLER_H */
