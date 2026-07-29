# Graph Report - .  (2026-07-29)

## Corpus Check
- cluster-only mode — file stats not available

## Summary
- 485 nodes · 1245 edges · 23 communities (22 shown, 1 thin omitted)
- Extraction: 94% EXTRACTED · 6% INFERRED · 0% AMBIGUOUS · INFERRED: 70 edges (avg confidence: 0.8)
- Token cost: 904 input · 796 output

## Graph Freshness
- Built from commit: `69cafc9b`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Basic JSON Types
- Terminal Utilities
- SAX Parser Callbacks
- Dialogue Tree
- JSON Input Formats
- JSON SAX Acceptor
- Random Event System
- Save/Load System
- Internationalization
- Game State
- Ending Tracker
- Room Registry
- Game Chapters
- JSON Value Internals
- JSON Output Formats
- Scene Registry
- Reverse Iterators
- EndingTracker Impl
- Game Initialization
- Ordered Map Allocator
- Get Reference Helper

## God Nodes (most connected - your core abstractions)
1. `string()` - 49 edges
2. `basic_json()` - 41 edges
3. `operator<()` - 39 edges
4. `GameState` - 36 edges
5. `handle_value()` - 30 edges
6. `push_back()` - 28 edges
7. `json_sax_dom_callback_parser` - 26 edges
8. `end()` - 26 edges
9. `begin()` - 25 edges
10. `size()` - 24 edges

## Surprising Connections (you probably didn't know these)
- `EndingTracker::register_ending()` --references--> `EndingDef`  [EXTRACTED]
  src/ending_tracker.cpp → include/ending_tracker.h
- `DialogueTree::start()` --references--> `GameState`  [EXTRACTED]
  src/dialogue_tree.cpp → include/game_state.h
- `RandomEventSystem::try_trigger()` --references--> `GameState`  [EXTRACTED]
  src/random_event.cpp → include/game_state.h
- `DialogueTree::load_from_json()` --references--> `string()`  [EXTRACTED]
  src/dialogue_tree.cpp → include/nlohmann/json.hpp
- `EndingTracker::is_unlocked()` --references--> `string()`  [EXTRACTED]
  src/ending_tracker.cpp → include/nlohmann/json.hpp

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Story Flow** — readme_chapter_1, readme_chapter_2, readme_chapter_3 [EXTRACTED 1.00]
- **Pluggable Extension Frameworks** — readme_game_state, readme_room_registry, readme_scene_registry, readme_dialogue_tree, readme_ending_tracker, readme_save_load, readme_random_event [EXTRACTED 1.00]

## Communities (23 total, 1 thin omitted)

### Community 0 - "Basic JSON Types"
Cohesion: 0.06
Nodes (104): array_t, BasicJsonType, boolean_t, byte_container_with_subtype, CompatibleType, const_iterator, const_reference, difference_type (+96 more)

### Community 1 - "Terminal Utilities"
Cohesion: 0.07
Nodes (43): flush_input(), try_getch(), a3_hell_print(), dire_mark(), go(), a1(), a1a(), a1aa() (+35 more)

### Community 2 - "SAX Parser Callbacks"
Cohesion: 0.08
Nodes (44): binary_t, back(), binary(), boolean(), empty(), end_array(), end_object(), get_number_float() (+36 more)

### Community 3 - "Dialogue Tree"
Cohesion: 0.08
Nodes (25): DialogueNode, id, on_enter_flag, options, speaker, text, DialogueOption, key (+17 more)

### Community 4 - "JSON Input Formats"
Cohesion: 0.22
Nodes (24): char_int_type, accept(), add(), array(), from_bjdata(), from_bson(), from_cbor(), from_msgpack() (+16 more)

### Community 5 - "JSON SAX Acceptor"
Cohesion: 0.13
Nodes (11): Exception, hex_bytes(), json_sax_acceptor, namespace(), NLOHMANN_JSON_NAMESPACE_BEGIN(), parse_error(), std::string to_string(), string_t_helper() (+3 more)

### Community 6 - "Random Event System"
Cohesion: 0.10
Nodes (18): function, map, vector, RandomEvent, condition, cooldown, description, effect (+10 more)

### Community 7 - "Save/Load System"
Cohesion: 0.14
Nodes (18): read_line_raw(), save_menu(), json, map, vector, delete_save(), from_json(), list_saves() (+10 more)

### Community 8 - "Internationalization"
Cohesion: 0.21
Nodes (7): vector, map, map, I18N, current_lang_, strings_, string()

### Community 9 - "Game State"
Cohesion: 0.14
Nodes (8): GameState, flags, inventory, quest_defs_, turn_count, visit_count, vector, QuestDef

### Community 10 - "Ending Tracker"
Cohesion: 0.14
Nodes (14): EndingDef, description, hidden, id, title, EndingTracker, check_all, endings_ (+6 more)

### Community 11 - "Room Registry"
Cohesion: 0.15
Nodes (12): json, operator "" _json(), RoomDef, east, id, name, north, south (+4 more)

### Community 12 - "Game Chapters"
Cohesion: 0.18
Nodes (14): Chapter 1, Chapter 2, Chapter 3, DialogueTree, EndingTracker, GameState, In the Abyss, Kenzaburō Ōe (+6 more)

### Community 13 - "JSON Value Internals"
Cohesion: 0.18
Nodes (12): false_type, data, m_type, m_value, dump_float(), dump_integer(), is_negative_number(), type() (+4 more)

### Community 14 - "JSON Output Formats"
Cohesion: 0.36
Nodes (10): decode(), vector, to_bjdata(), to_bson(), to_cbor(), to_msgpack(), to_ubjson(), output_adapter (+2 more)

### Community 15 - "Scene Registry"
Cohesion: 0.29
Nodes (6): SceneDef, chapter, id, is_unlocked, label, register_scene()

### Community 16 - "Reverse Iterators"
Cohesion: 0.53
Nodes (6): const_reverse_iterator, crbegin(), crend(), rbegin(), rend(), reverse_iterator

### Community 18 - "Game Initialization"
Cohesion: 0.53
Nodes (5): Alph(), Dire(), init_game(), quit(), register_legacy_scenes()

### Community 19 - "Ordered Map Allocator"
Cohesion: 0.40
Nodes (5): Allocator, ordered_map, initializer_list, It, value_type

### Community 20 - "Get Reference Helper"
Cohesion: 0.50
Nodes (4): get_ref(), get_ref_impl(), ReferenceType, ThisType

## Knowledge Gaps
- **80 isolated node(s):** `key`, `label`, `next_node_id`, `set_flag`, `required_flag` (+75 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **1 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `string()` connect `Internationalization` to `Basic JSON Types`, `Terminal Utilities`, `SAX Parser Callbacks`, `Dialogue Tree`, `JSON SAX Acceptor`, `Random Event System`, `Save/Load System`, `Game State`, `Ending Tracker`, `Room Registry`, `Scene Registry`, `EndingTracker Impl`, `Game Initialization`?**
  _High betweenness centrality (0.509) - this node is a cross-community bridge._
- **Why does `GameState` connect `Game State` to `Terminal Utilities`, `Dialogue Tree`, `Random Event System`, `Save/Load System`, `Internationalization`, `Game Initialization`?**
  _High betweenness centrality (0.087) - this node is a cross-community bridge._
- **Why does `text()` connect `Terminal Utilities` to `Internationalization`?**
  _High betweenness centrality (0.053) - this node is a cross-community bridge._
- **What connects `key`, `label`, `next_node_id` to the rest of the system?**
  _80 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Basic JSON Types` be split into smaller, more focused modules?**
  _Cohesion score 0.056420906888196606 - nodes in this community are weakly interconnected._
- **Should `Terminal Utilities` be split into smaller, more focused modules?**
  _Cohesion score 0.07019230769230769 - nodes in this community are weakly interconnected._
- **Should `SAX Parser Callbacks` be split into smaller, more focused modules?**
  _Cohesion score 0.07743496672716274 - nodes in this community are weakly interconnected._