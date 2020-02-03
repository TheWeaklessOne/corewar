/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:48:04 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:18 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_4bits				swap_bits(unsigned char nb)
{
	t_4bits			ret;
	unsigned		save;

	ret.arg = nb;
	save = ret.field.arg_3;
	ret.field.arg_3 = ret.field.arg_0;
	ret.field.arg_0 = save;
	save = ret.field.arg_2;
	ret.field.arg_2 = ret.field.arg_1;
	ret.field.arg_1 = save;
	return (ret);
}

void				get_arg_types(unsigned char c, unsigned *args)
{
	t_4bits			bits;

	bits = swap_bits(c);
	(bits.field.arg_0 == REG_CODE) ? args[0] = T_REG : 0;
	(bits.field.arg_0 == DIR_CODE) ? args[0] = T_DIR : 0;
	(bits.field.arg_0 == IND_CODE) ? args[0] = T_IND : 0;
	(bits.field.arg_1 == REG_CODE) ? args[1] = T_REG : 0;
	(bits.field.arg_1 == DIR_CODE) ? args[1] = T_DIR : 0;
	(bits.field.arg_1 == IND_CODE) ? args[1] = T_IND : 0;
	(bits.field.arg_2 == REG_CODE) ? args[2] = T_REG : 0;
	(bits.field.arg_2 == DIR_CODE) ? args[2] = T_DIR : 0;
	(bits.field.arg_2 == IND_CODE) ? args[2] = T_IND : 0;
	args[3] = bits.field.arg_3;
}

unsigned			read_t_dir(t_vm *vm, unsigned char pos, int size)
{
	t_4bytes		ret;

	if (size == 4)
	{
		ret.field.octet1 = vm->arena[(pos + 3) % MEM_SIZE];
		ret.field.octet2 = vm->arena[(pos + 2) % MEM_SIZE];
		ret.field.octet3 = vm->arena[(pos + 1)  % MEM_SIZE];
		ret.field.octet4 = vm->arena[pos];
	}
	else
	{
		ret.field.octet1 = vm->arena[(pos + 1) % MEM_SIZE];
		ret.field.octet2 = vm->arena[pos];
		ret.field.octet3 = 0;
		ret.field.octet4 = 0;
	}
	return (ret.hex);
}

unsigned			read_t_ind(t_vm *vm, unsigned char pos, unsigned char cur_pos)
{
	t_4bytes		ret;
	t_4bytes		arg;
	int				skip;

	arg.field.octet4 = vm->arena[pos];
	arg.field.octet3 = vm->arena[(pos + 1)  % MEM_SIZE];
	arg.field.octet2 = vm->arena[(pos + 2)  % MEM_SIZE];
	arg.field.octet1 = vm->arena[(pos + 3)  % MEM_SIZE];
	skip = arg.hex;
	ret.field.octet4 = vm->arena[(cur_pos + skip % IDX_MOD) % MEM_SIZE];
	ret.field.octet3 = vm->arena[(cur_pos + (skip + 1) % IDX_MOD) % MEM_SIZE];
	ret.field.octet2 = vm->arena[(cur_pos + (skip + 2) % IDX_MOD) % MEM_SIZE];
	ret.field.octet1 = vm->arena[(cur_pos + (skip + 2) % IDX_MOD) % MEM_SIZE];
	return (ret.hex);
}

void				read_args(t_vm *vm, t_cur *cur)
{
	if (cur->args_type[0] == T_REG)
		cur->args[0] = vm->arena[(cur->pos + 2) % MEM_SIZE];
	else if (cur->args_type[0] == T_DIR)
		cur->args[0] = read_t_dir(vm, (cur->pos + 2) % MEM_SIZE, cur->arg_size[1]);
	else if (cur->args_type[0] == T_IND)
		cur->args[0] = read_t_ind(vm, (cur->pos + 2) % MEM_SIZE, cur->pos);
	if (cur->args_type[1] == T_REG)
		cur->args[1] = vm->arena[(cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE];
	else if (cur->args_type[1] == T_DIR)
		cur->args[1] = read_t_dir(vm, (cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE, cur->arg_size[1]);
	else if (cur->args_type[1] == T_IND)
		cur->args[1] = read_t_ind(vm, (cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE, cur->pos);
	if (cur->args_type[2] == T_REG)
		cur->args[2] = vm->arena[(cur->pos + 2 + cur->arg_size[0] + cur->arg_size[1]) % MEM_SIZE];
	else if (cur->args_type[2] == T_DIR)
		cur->args[2] = read_t_dir(vm, (cur->pos + 2 + cur->arg_size[0] + cur->arg_size[1]) % MEM_SIZE, cur->arg_size[2]);
	else if (cur->args_type[2] == T_IND)
		cur->args[1] = read_t_ind(vm, (cur->pos + 2 + cur->arg_size[0] + cur->arg_size[1]) % MEM_SIZE, cur->pos);
}

void				do_sti(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{
	read_args(vm, cur);
	vm->arena[(cur->pos + (cur->args[1] + cur->args[2]) % IDX_MOD) % MEM_SIZE] =
			cur->reg[cur->args[0]];
}

void				do_live(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{
	cur->last_cyc_live = vm->global;
	vm->live_count++;
	if (cur->id_player == read_t_dir(vm, cur->pos + 1, 4))
		vm->champ[cur->id_player]->last_alive = vm->global;
}

void				do_ld(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{
	read_args(vm, cur);
	if (cur->args[0] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
	cur->reg[cur->args[1]] = cur->args[0];
}

void				do_zjmp(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{

	if (cur->carry)
		cur->pos = (cur->pos + (read_t_dir(vm, cur->pos + 1, 4) % IDX_MOD)) % MEM_SIZE;
}

void				do_op(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{
	(cur->operation == 1) ? do_live(vm, cur, op_tab) : 0;
	(cur->operation == 2) ? do_ld(vm, cur, op_tab) : 0;
//	(cur->operation == 3) ? do_st(vm, cur, op_tab) : 0;
//	(cur->operation == 4) ? do_add(vm, cur, op_tab) : 0;
//	(cur->operation == 5) ? do_sub(vm, cur, op_tab) : 0;
//	(cur->operation == 6) ? do_and(vm, cur, op_tab) : 0;
//	(cur->operation == 7) ? do_or(vm, cur, op_tab) : 0;
//	(cur->operation == 8) ? do_xor(vm, cur, op_tab) : 0;
	(cur->operation == 9) ? do_zjmp(vm, cur, op_tab) : 0;
//	(cur->operation == 10) ? do_ldi(vm, cur, op_tab) : 0;
	(cur->operation == 11) ? do_sti(vm, cur, op_tab) : 0;
//	(cur->operation == 12) ? do_fork(vm, cur, op_tab) : 0;
//	(cur->operation == 13) ? do_lld(vm, cur, op_tab) : 0;
//	(cur->operation == 14) ? do_lldi(vm, cur, op_tab) : 0;
//	(cur->operation == 15) ? do_lfork(vm, cur, op_tab) : 0;
//	(cur->operation == 16) ? do_aff(vm, cur, op_tab) : 0;
}

void				calc_arg_size(unsigned *args_t, int *arg_size, int size)
{
	(args_t[0] == T_IND) ? arg_size[0] = IND_SIZE : 0;
	(args_t[0] == T_REG) ? arg_size[0] = 1 : 0;
	(args_t[0] == T_DIR) ? arg_size[0] = (4 - 2 * size) : 0;
	(args_t[1] == T_IND) ? arg_size[1] = IND_SIZE : 0;
	(args_t[1] == T_REG) ? arg_size[1] = 1 : 0;
	(args_t[1] == T_DIR) ? arg_size[1] = (4 - 2 * size) : 0;
	(args_t[2] == T_IND) ? arg_size[2] = IND_SIZE : 0;
	(args_t[2] == T_REG) ? arg_size[2] = 1 : 0;
	(args_t[2] == T_DIR) ? arg_size[2] = (4 - 2 * size) : 0;
}

int					check_t_reg(t_vm *vm, t_cur *cur, unsigned *args_t)
{
	int				reg;

	if (args_t[0] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	if (args_t[1] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	if (args_t[2] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2 + cur->arg_size[0] +
				  cur->arg_size[1]) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	return (1);
}

int					check_op(t_vm *vm, t_cur *cur, const t_op op_tab[17])
{
	t_op			op;

	if (cur->operation >= 0x01 && cur->operation <= 0x10)
	{
		op = op_tab[cur->operation];
		if (op.code_type_arg)
		{
			get_arg_types(vm->arena[(cur->pos + 1) % MEM_SIZE], cur->args_type);
			calc_arg_size(cur->args_type, cur->arg_size, op.dir_size);
			if ((cur->args_type[0] & op.arg_type[0]) && (cur->args_type[1] & op.arg_type[1]) &&
				(cur->args_type[2] & op.arg_type[2]) && cur->args_type[3] == 0)
				if (check_t_reg(vm, cur, cur->args_type))
					return (0);
			return (2 + cur->arg_size[0] + cur->arg_size[1] + cur->arg_size[2]);
		}
		return (0);
	}
	return (1);
}

void				do_cycle(t_vm *vm, const t_op op_tab[17])
{
	t_cur			*cur;
	int				skip;

	cur = vm->curs;
	while (cur)
	{
		if (cur->cyc_before_op == 0)
			if ((cur->operation = vm->arena[cur->pos]) >= 0x01
				&& cur->operation <= 0x10)
				cur->cyc_before_op = op_tab[cur->operation].need_cycles;
		if (--cur->cyc_before_op <= 1000)
		{
			if (!(skip = check_op(vm, cur, op_tab)))
			{
				do_op(vm, cur, op_tab);
				cur->pos = (cur->pos + 2 + cur->arg_size[0] +
						cur->arg_size[1] + cur->arg_size[2]) % MEM_SIZE;
			}
			else
				cur->pos = (cur->pos + skip) % MEM_SIZE;
		}
		cur = cur->next;
	}
}

void				put_winner(t_vm *vm)
{
	unsigned		max[2];
	int				i;

	i = -1;
	max[0] = 0;
	while (++i < vm->players)
	{
		if (vm->champ[i]->last_alive >= max[0])
		{
			max[0] = vm->champ[i]->last_alive;
			max[1] = i;
		}
	}
	printf("Player %d - \"%s\" (\"%s\") - won!\n", vm->champ[max[1]]->n + 1, vm->champ[max[1]]->name, vm->champ[max[1]]->com);
}

t_cur			*cur_at(t_cur *cur, int at)
{
	t_cur		*ret;
	int			i;

	if (!cur)
		return (NULL);
	if (at <= 0)
		return (cur);
	ret = cur;
	i = 1;
	while (cur->next && i < at)
	{
		cur = cur->next;
		i++;
	}
	if (i == at)
		return (cur);
	return (ret);
}

t_cur			*cur_remove_at(t_cur *cur, int at)
{
	t_cur		*lst_at;
	t_cur		*lst_before;

	if (!(lst_at = cur_at(cur, at)))
		return (NULL);
	if (lst_at == cur && at != 1)
		return (cur);
	if (at == 1)
	{
		lst_before = cur;
		cur = cur->next;
		free(lst_before);
		lst_before = NULL;
	}
	else
	{
		lst_before = cur_at(cur, at - 1);
		lst_before->next = lst_at->next;
		free(lst_at);
		lst_at = NULL;
	}
	return (cur);
}


void				delete_deads(t_vm *vm)
{
	t_cur			*cur;
	int				at;

	at = 1;
	cur = vm->curs;
	while (cur)
	{
		if (vm->cycles_to_die <= 0 || vm->global - cur->last_cyc_live <= vm->cycles_to_die)
		{
			vm->curs = cur_remove_at(vm->curs, at);
			vm->curs_alive--;
		}
		at++;
		cur = cur->next;
	}
}

int					war_coming(t_vm *vm)
{
	const t_op		op_tab[17] = {
			{0, 0, {0}, 0, 0, 0, 0, 0},
			{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
			{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
			{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
			{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
			{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
			{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
			{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,	"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
			{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,	"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
			{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
			{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,"load index", 1, 1},
			{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
			{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
			{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
			{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
			{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
			{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}};
	while (++vm->global)
	{
		if ((vm->cycles_to_die > 0) ? !(vm->global % vm->cycles_to_die) : 1)
		{
			vm->checks++;
			delete_deads(vm);
			if (vm->live_count >= NBR_LIVE)
				vm->cycles_to_die -= CYCLE_DELTA;
			if (vm->checks == MAX_CHECKS)
			{
				vm->cycles_to_die -= CYCLE_DELTA;
				vm->checks = 0;
			}
			vm->live_count = 0;
		}
		do_cycle(vm, op_tab);
		if (vm->curs_alive == 0)
			break ;
	}
	put_winner(vm);
	return (1);
}
