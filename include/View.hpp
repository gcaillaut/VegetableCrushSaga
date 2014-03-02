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

		virtual void loop () = 0;
		bool isRunning() const;

		void activate ();

	protected:
		Controller *controller;
		bool running;
};



#endif /* INCLUDED_VIEW_H */
