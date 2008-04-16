/* Handler subclass. A Handler takes a window and draws "stuff" on it until
 * it is finished. It contains the Window to draw on and a function pointer
 * to call when it is finished.
 */

class Handler
{
		Handler( Molinator_Window w, void (*pt)(void) )
			: win(w), cb_done(pt)
		{		}

	private:
		//takes a void argument because it can either be a string name or a score
		void (*cb_done)(void);
		Molinator_Window win;
};
