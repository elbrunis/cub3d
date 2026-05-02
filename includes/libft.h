#ifndef LIBFT_H
# define LIBFT_H
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s);
char	*ft_strdup(const char *s1);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

char	*get_next_line(int fd);

#endif