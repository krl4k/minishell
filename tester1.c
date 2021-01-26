//
// Created by Magnemite Winter on 1/26/21.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct		s_list
{
    void			*content;
    struct s_list	*next;
    struct s_list	*prev;
}					t_list;

t_list	*ft_lstlast(t_list *lst)
{
    t_list *temp;

    if (!lst)
        return (NULL);
    temp = lst;
    while (temp->next)
        temp = temp->next;
    return (temp);
}

void	list_init(t_list **lst, t_list *new)
{
    t_list *last_elem;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last_elem = ft_lstlast(*lst);
    last_elem->next = new;
    new->prev = last_elem;
}

void	make_full_ring(t_list **cam_lst)
{
    t_list *end;

    end = *cam_lst;
    while (end->next)
    {
        end = end->next;
    }
    (*cam_lst)->prev = end;
    end->next = *cam_lst;
}

t_list	*ft_lstnew(void *content)
{
    t_list *new;

    if (!(new = (t_list *)malloc(sizeof(t_list))))
        return (NULL);
    if (!content)
        new->content = NULL;
    else
        new->content = content;
    new->next = NULL;
    return (new);
}

int main(int ac, char **av)
{
    int i = 0;
    while (av[i])
    {
        list_init(ft_lstnew(av[i++]));
    }
}
