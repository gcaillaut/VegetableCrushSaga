#ifndef INCLUDED_VIEW_H
#define INCLUDED_VIEW_H

class Controller;

class View
{
	public:
		View (Controller *controller);
		virtual ~View () = 0;

		virtual void clear () = 0;
		virtual void draw () = 0;
		virtual void display () = 0;

		virtual void sendEvents () = 0;

	protected:
		Controller *controller;
};



#endif /* INCLUDED_VIEW_H */
