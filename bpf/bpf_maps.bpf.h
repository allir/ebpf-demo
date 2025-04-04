#ifndef BPF_MAPS_H
#define BPF_MAPS_H

// Generic map macro
#define BPF_MAP(_name, _type, _key_type, _value_type, _max_entries) \
	struct {                                                    \
		__uint(type, _type);                                \
		__uint(max_entries, _max_entries);                  \
		__type(key, _key_type);                             \
		__type(value, _value_type);                         \
	} _name SEC(".maps");

// BPF_MAP_TYPE_HASH
#define BPF_HASH(_name, _key_type, _value_type, _max_entries) \
	BPF_MAP(_name, BPF_MAP_TYPE_HASH, _key_type, _value_type, _max_entries)

// BPF_MAP_TYPE_LRU_HASH
#define BPF_LRU_HASH(_name, _key_type, _value_type, _max_entries) \
	BPF_MAP(_name, BPF_MAP_TYPE_LRU_HASH, _key_type, _value_type, _max_entries)

// BPF_MAP_TYPE_ARRAY
#define BPF_ARRAY(_name, _value_type, _max_entries) \
	BPF_MAP(_name, BPF_MAP_TYPE_ARRAY, u32, _value_type, _max_entries)

// BPF_MAP_TYPE_PERCPU_ARRAY
#define BPF_PERCPU_ARRAY(_name, _value_type, _max_entries) \
	BPF_MAP(_name, BPF_MAP_TYPE_PERCPU_ARRAY, u32, _value_type, _max_entries)

// BPF_MAP_TYPE_PROG_ARRAY
#define BPF_PROG_ARRAY(_name, _max_entries) \
	BPF_MAP(_name, BPF_MAP_TYPE_PROG_ARRAY, u32, u32, _max_entries)

// BPF_MAP_TYPE_PERF_EVENT_ARRAY
#define BPF_PERF_OUTPUT(_name)                               \
	struct {                                             \
		__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY); \
		__uint(key_size, sizeof(u32));               \
		__uint(value_size, sizeof(u32));             \
	} _name SEC(".maps");

// BPF_MAP_TYPE_RINGBUF
#define BPF_RINGBUF(_name, _max_entries)            \
	struct {                                    \
		__uint(type, BPF_MAP_TYPE_RINGBUF); \
		__uint(max_entries, _max_entries);  \
	} _name SEC(".maps");

// BPF_MAP_TYPE_LPM_TRIE
#define BPF_LPM_TRIE(_name, _key_type, _value_type, _max_entries) \
	struct {                                                  \
		__uint(type, BPF_MAP_TYPE_LPM_TRIE);              \
		__type(key, _key_type);                           \
		__type(value, _value_type);                       \
		__uint(map_flags, BPF_F_NO_PREALLOC);             \
		__uint(max_entries, _max_entries);                \
	} _name SEC(".maps");

#endif /* BPF_MAPS_H */
