#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "binary.h"
#include "xor_sum.h"

template <size_t elder_bit, size_t _index, size_t Head, size_t... Tail>
struct get_heap {
  static constexpr size_t index =
      _index * GetBit<elder_bit, Head>::value +
      !(GetBit<elder_bit, Head>::value) *
          get_heap<elder_bit, _index + 1, Tail...>::index;
  static constexpr size_t heap =
      Head * GetBit<elder_bit, Head>::value +
      !(GetBit<elder_bit, Head>::value) *
          get_heap<elder_bit, _index + 1, Tail...>::heap;
};

template <size_t elder_bit, size_t _index, size_t Head>
struct get_heap<elder_bit, _index, Head> {
  static constexpr size_t index = _index * GetBit<elder_bit, Head>::value +
                                  !(GetBit<elder_bit, Head>::value) * (-1);
  static constexpr size_t heap = Head * GetBit<elder_bit, Head>::value +
                                 !(GetBit<elder_bit, Head>::value) * (-1);
};

template <size_t... Heaps>
struct Game {
  static constexpr bool first_player_wins = XorSum<Heaps...>::value;
  static constexpr size_t elder_bit_of_game =
      Log2<XorSum<Heaps...>::value>::value;
  static constexpr ssize_t first_move_heap_index =
      first_player_wins * get_heap<elder_bit_of_game, 0, Heaps...>::index +
      (!first_player_wins) * (-1);
  static constexpr ssize_t first_move_rocks_count =
      first_player_wins *
          (get_heap<elder_bit_of_game, 0, Heaps...>::heap -
           XorSum<XorSum<Heaps...>::value,
                  get_heap<elder_bit_of_game, 0, Heaps...>::heap>::value) +
      (!first_player_wins) * (-1);
};

#endif  /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
