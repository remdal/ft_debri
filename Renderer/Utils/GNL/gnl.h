/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: gnl.h            +++     +++					**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 22/09/2025 11:20:26      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_read_before_newline(int fd, char *leftover);
char	*ft_line_from_leftover(char *leftover);
char	*ft_trim_leftover(char *leftover);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *leftover, char *buff);
char	*ft_strcat(char *str, char *buff);
char	*ft_strcpy(char *str, char *leftover);

#endif