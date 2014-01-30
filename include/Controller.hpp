#ifndef INCLUDED_CONTROLLER_H
#define INCLUDED_CONTROLLER_H

class View;

class Controller
{
public:
  Controller ();
  virtual ~Controller () = 0;

  virtual void onClick (const float x, const float y) = 0;
  virtual void onClickRelease (const float x, const float y) = 0;
  virtual void onLostFocus () = 0;
  virtual void onGainedFocus () = 0;

  void setView (View *view);

private:
  View *current_view;
};


#endif /* INCLUDED_CONTROLLER_H */
