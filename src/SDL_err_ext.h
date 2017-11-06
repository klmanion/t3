//SDL_err_ext.h

#ifndef __SDL_ERR_EXT__
#define __SDL_ERR_EXT__

#include <stdlib.h>
#include <stdarg.h>
#include <err.h>

__BEGIN_DECLS
void	SDL_errx __P((int,const char*,...)) __dead2;
void	SDL_err __P((int,const char*,...)) __dead2;
void	SDL_die __P((void)) __dead2;
__END_DECLS

#endif /* __SDL_ERR_EXT__ */
