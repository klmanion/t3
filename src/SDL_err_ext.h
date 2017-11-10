//SDL_err_ext.h

#ifndef _SDL_ERR_EXT_H_
#define _SDL_ERR_EXT_H_

#include <stdlib.h>
#include <stdarg.h>
#include <err.h>

__BEGIN_DECLS
void	SDL_errx __P((int,const char*,...)) __printflike(2,3) __dead2;
void	SDL_err __P((int,const char*,...)) __printflike(2,3) __dead2;
void	SDL_die __P((void)) __dead2;
__END_DECLS

#endif /* !_SDL_ERR_EXT_H_ */
