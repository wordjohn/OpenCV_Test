// fbc_cv is free software and uses the same licence as FFmpeg
// Email: fengbingchun@163.com

#ifndef FBC_CV_OPTIONS_TABLE_HPP_
#define FBC_CV_OPTIONS_TABLE_HPP_

// reference: ffmpeg 4.2
//            libavformat/options_table.h

#ifdef _MSC_VER

#include "avoption.hpp"
#include "avformat.hpp"
#include "avio.hpp"

namespace fbc {

#define OFFSET(x) offsetof(AVFormatContext,x)
#define DEFAULT 0 //should be NAN but it does not work as it is not a constant in glibc as required by ANSI/ISO C
//these names are too long to be readable
#define E AV_OPT_FLAG_ENCODING_PARAM
#define D AV_OPT_FLAG_DECODING_PARAM

static const AVOption avformat_options[] = {
	{ "avioflags", NULL, OFFSET(avio_flags), AV_OPT_TYPE_FLAGS, { DEFAULT }, INT_MIN, INT_MAX, D | E, "avioflags" },
	{ "direct", "reduce buffering", 0, AV_OPT_TYPE_CONST, { AVIO_FLAG_DIRECT }, INT_MIN, INT_MAX, D | E, "avioflags" },
	{ "probesize", "set probing size", OFFSET(probesize), AV_OPT_TYPE_INT64, { 5000000 }, 32, INT64_MAX, D },
	{ "formatprobesize", "number of bytes to probe file format", OFFSET(format_probesize), AV_OPT_TYPE_INT, { PROBE_BUF_MAX }, 0, INT_MAX - 1, D },
	{ "packetsize", "set packet size", OFFSET(packet_size), AV_OPT_TYPE_INT, { DEFAULT }, 0, INT_MAX, E },
	{ "fflags", NULL, OFFSET(flags), AV_OPT_TYPE_FLAGS, { AVFMT_FLAG_AUTO_BSF }, INT_MIN, INT_MAX, D | E, "fflags" },
	{ "flush_packets", "reduce the latency by flushing out packets immediately", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_FLUSH_PACKETS }, INT_MIN, INT_MAX, E, "fflags" },
	{ "ignidx", "ignore index", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_IGNIDX }, INT_MIN, INT_MAX, D, "fflags" },
	{ "genpts", "generate pts", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_GENPTS }, INT_MIN, INT_MAX, D, "fflags" },
	{ "nofillin", "do not fill in missing values that can be exactly calculated", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_NOFILLIN }, INT_MIN, INT_MAX, D, "fflags" },
	{ "noparse", "disable AVParsers, this needs nofillin too", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_NOPARSE }, INT_MIN, INT_MAX, D, "fflags" },
	{ "igndts", "ignore dts", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_IGNDTS }, INT_MIN, INT_MAX, D, "fflags" },
	{ "discardcorrupt", "discard corrupted frames", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_DISCARD_CORRUPT }, INT_MIN, INT_MAX, D, "fflags" },
	{ "sortdts", "try to interleave outputted packets by dts", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_SORT_DTS }, INT_MIN, INT_MAX, D, "fflags" },
#if FF_API_LAVF_KEEPSIDE_FLAG
	{ "keepside", "deprecated, does nothing", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_KEEP_SIDE_DATA }, INT_MIN, INT_MAX, D, "fflags" },
#endif
	{ "fastseek", "fast but inaccurate seeks", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_FAST_SEEK }, INT_MIN, INT_MAX, D, "fflags" },
#if FF_API_LAVF_MP4A_LATM
	{ "latm", "deprecated, does nothing", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_MP4A_LATM }, INT_MIN, INT_MAX, E, "fflags" },
#endif
	{ "nobuffer", "reduce the latency introduced by optional buffering", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_NOBUFFER }, 0, INT_MAX, D, "fflags" },
	{ "bitexact", "do not write random/volatile data", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_BITEXACT }, 0, 0, E, "fflags" },
	{ "shortest", "stop muxing with the shortest stream", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_SHORTEST }, 0, 0, E, "fflags" },
	{ "autobsf", "add needed bsfs automatically", 0, AV_OPT_TYPE_CONST, { AVFMT_FLAG_AUTO_BSF }, 0, 0, E, "fflags" },
	{ "seek2any", "allow seeking to non-keyframes on demuxer level when supported", OFFSET(seek2any), AV_OPT_TYPE_BOOL, { 0 }, 0, 1, D },
	{ "analyzeduration", "specify how many microseconds are analyzed to probe the input", OFFSET(max_analyze_duration), AV_OPT_TYPE_INT64, { 0 }, 0, INT64_MAX, D },
	{ "cryptokey", "decryption key", OFFSET(key), AV_OPT_TYPE_BINARY, { 0, 0. }, 0, 0, D },
	{ "indexmem", "max memory used for timestamp index (per stream)", OFFSET(max_index_size), AV_OPT_TYPE_INT, { 1 << 20 }, 0, INT_MAX, D },
	{ "rtbufsize", "max memory used for buffering real-time frames", OFFSET(max_picture_buffer), AV_OPT_TYPE_INT, { 3041280 }, 0, INT_MAX, D }, /* defaults to 1s of 15fps 352x288 YUYV422 video */
	{ "fdebug", "print specific debug info", OFFSET(debug), AV_OPT_TYPE_FLAGS, { DEFAULT }, 0, INT_MAX, E | D, "fdebug" },
	{ "ts", NULL, 0, AV_OPT_TYPE_CONST, { FF_FDEBUG_TS }, INT_MIN, INT_MAX, E | D, "fdebug" },
	{ "max_delay", "maximum muxing or demuxing delay in microseconds", OFFSET(max_delay), AV_OPT_TYPE_INT, { -1 }, -1, INT_MAX, E | D },
	{ "start_time_realtime", "wall-clock time when stream begins (PTS==0)", OFFSET(start_time_realtime), AV_OPT_TYPE_INT64, { AV_NOPTS_VALUE }, INT64_MIN, INT64_MAX, E },
	{ "fpsprobesize", "number of frames used to probe fps", OFFSET(fps_probe_size), AV_OPT_TYPE_INT, { -1 }, -1, INT_MAX - 1, D },
	{ "audio_preload", "microseconds by which audio packets should be interleaved earlier", OFFSET(audio_preload), AV_OPT_TYPE_INT, { 0 }, 0, INT_MAX - 1, E },
	{ "chunk_duration", "microseconds for each chunk", OFFSET(max_chunk_duration), AV_OPT_TYPE_INT, { 0 }, 0, INT_MAX - 1, E },
	{ "chunk_size", "size in bytes for each chunk", OFFSET(max_chunk_size), AV_OPT_TYPE_INT, { 0 }, 0, INT_MAX - 1, E },
	/* this is a crutch for avconv, since it cannot deal with identically named options in different contexts.
	* to be removed when avconv is fixed */
	{ "f_err_detect", "set error detection flags (deprecated; use err_detect, save via avconv)", OFFSET(error_recognition), AV_OPT_TYPE_FLAGS, { AV_EF_CRCCHECK }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "err_detect", "set error detection flags", OFFSET(error_recognition), AV_OPT_TYPE_FLAGS, { AV_EF_CRCCHECK }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "crccheck", "verify embedded CRCs", 0, AV_OPT_TYPE_CONST, { AV_EF_CRCCHECK }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "bitstream", "detect bitstream specification deviations", 0, AV_OPT_TYPE_CONST, { AV_EF_BITSTREAM }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "buffer", "detect improper bitstream length", 0, AV_OPT_TYPE_CONST, { AV_EF_BUFFER }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "explode", "abort decoding on minor error detection", 0, AV_OPT_TYPE_CONST, { AV_EF_EXPLODE }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "ignore_err", "ignore errors", 0, AV_OPT_TYPE_CONST, { AV_EF_IGNORE_ERR }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "careful", "consider things that violate the spec, are fast to check and have not been seen in the wild as errors", 0, AV_OPT_TYPE_CONST, { AV_EF_CAREFUL }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "compliant", "consider all spec non compliancies as errors", 0, AV_OPT_TYPE_CONST, { AV_EF_COMPLIANT }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "aggressive", "consider things that a sane encoder shouldn't do as an error", 0, AV_OPT_TYPE_CONST, { AV_EF_AGGRESSIVE }, INT_MIN, INT_MAX, D, "err_detect" },
	{ "use_wallclock_as_timestamps", "use wallclock as timestamps", OFFSET(use_wallclock_as_timestamps), AV_OPT_TYPE_BOOL, { 0 }, 0, 1, D },
	{ "skip_initial_bytes", "set number of bytes to skip before reading header and frames", OFFSET(skip_initial_bytes), AV_OPT_TYPE_INT64, { 0 }, 0, INT64_MAX - 1, D },
	{ "correct_ts_overflow", "correct single timestamp overflows", OFFSET(correct_ts_overflow), AV_OPT_TYPE_BOOL, { 1 }, 0, 1, D },
	{ "flush_packets", "enable flushing of the I/O context after each packet", OFFSET(flush_packets), AV_OPT_TYPE_INT, { -1 }, -1, 1, E },
	{ "metadata_header_padding", "set number of bytes to be written as padding in a metadata header", OFFSET(metadata_header_padding), AV_OPT_TYPE_INT, { -1 }, -1, INT_MAX, E },
	{ "output_ts_offset", "set output timestamp offset", OFFSET(output_ts_offset), AV_OPT_TYPE_DURATION, { 0 }, -INT64_MAX, INT64_MAX, E },
	{ "max_interleave_delta", "maximum buffering duration for interleaving", OFFSET(max_interleave_delta), AV_OPT_TYPE_INT64, { 10000000 }, 0, INT64_MAX, E },
	{ "f_strict", "how strictly to follow the standards (deprecated; use strict, save via avconv)", OFFSET(strict_std_compliance), AV_OPT_TYPE_INT, { DEFAULT }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "strict", "how strictly to follow the standards", OFFSET(strict_std_compliance), AV_OPT_TYPE_INT, { DEFAULT }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "very", "strictly conform to a older more strict version of the spec or reference software", 0, AV_OPT_TYPE_CONST, { FF_COMPLIANCE_VERY_STRICT }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "strict", "strictly conform to all the things in the spec no matter what the consequences", 0, AV_OPT_TYPE_CONST, { FF_COMPLIANCE_STRICT }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "normal", NULL, 0, AV_OPT_TYPE_CONST, { FF_COMPLIANCE_NORMAL }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "unofficial", "allow unofficial extensions", 0, AV_OPT_TYPE_CONST, { FF_COMPLIANCE_UNOFFICIAL }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "experimental", "allow non-standardized experimental variants", 0, AV_OPT_TYPE_CONST, { FF_COMPLIANCE_EXPERIMENTAL }, INT_MIN, INT_MAX, D | E, "strict" },
	{ "max_ts_probe", "maximum number of packets to read while waiting for the first timestamp", OFFSET(max_ts_probe), AV_OPT_TYPE_INT, { 50 }, 0, INT_MAX, D },
	{ "avoid_negative_ts", "shift timestamps so they start at 0", OFFSET(avoid_negative_ts), AV_OPT_TYPE_INT, { -1 }, -1, 2, E, "avoid_negative_ts" },
	{ "auto", "enabled when required by target format", 0, AV_OPT_TYPE_CONST, { AVFMT_AVOID_NEG_TS_AUTO }, INT_MIN, INT_MAX, E, "avoid_negative_ts" },
	{ "disabled", "do not change timestamps", 0, AV_OPT_TYPE_CONST, { 0 }, INT_MIN, INT_MAX, E, "avoid_negative_ts" },
	{ "make_non_negative", "shift timestamps so they are non negative", 0, AV_OPT_TYPE_CONST, { AVFMT_AVOID_NEG_TS_MAKE_NON_NEGATIVE }, INT_MIN, INT_MAX, E, "avoid_negative_ts" },
	{ "make_zero", "shift timestamps so they start at 0", 0, AV_OPT_TYPE_CONST, { AVFMT_AVOID_NEG_TS_MAKE_ZERO }, INT_MIN, INT_MAX, E, "avoid_negative_ts" },
	{ "dump_separator", "set information dump field separator", OFFSET(dump_separator), AV_OPT_TYPE_STRING, { 0, 0., ", " }, CHAR_MIN, CHAR_MAX, D | E },
	{ "codec_whitelist", "List of decoders that are allowed to be used", OFFSET(codec_whitelist), AV_OPT_TYPE_STRING, { 0, 0., NULL }, CHAR_MIN, CHAR_MAX, D },
	{ "format_whitelist", "List of demuxers that are allowed to be used", OFFSET(format_whitelist), AV_OPT_TYPE_STRING, { 0, 0., NULL }, CHAR_MIN, CHAR_MAX, D },
	{ "protocol_whitelist", "List of protocols that are allowed to be used", OFFSET(protocol_whitelist), AV_OPT_TYPE_STRING, { 0, 0., NULL }, CHAR_MIN, CHAR_MAX, D },
	{ "protocol_blacklist", "List of protocols that are not allowed to be used", OFFSET(protocol_blacklist), AV_OPT_TYPE_STRING, { 0, 0., NULL }, CHAR_MIN, CHAR_MAX, D },
	{ "max_streams", "maximum number of streams", OFFSET(max_streams), AV_OPT_TYPE_INT, { 1000 }, 0, INT_MAX, D },
	{ "skip_estimate_duration_from_pts", "skip duration calculation in estimate_timings_from_pts", OFFSET(skip_estimate_duration_from_pts), AV_OPT_TYPE_BOOL, { 0 }, 0, 1, D },
	{ "max_probe_packets", "Maximum number of packets to probe a codec", OFFSET(max_probe_packets), AV_OPT_TYPE_INT, { 2500 }, 0, INT_MAX, D },
	{ NULL },
};

#undef E
#undef D
#undef DEFAULT
#undef OFFSET

} // namespace fbc

#endif // _MSC_VER
#endif // FBC_CV_OPTIONS_TABLE_HPP_
