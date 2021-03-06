///
///
/// FACILITY    : String Utilities and Log Managements
///
/// FILE NAME   : strlogutil.h
///
/// ABSTRACT    : Constant & Header of String Utilities and Log Managements
///
/// AUTHOR      : Thanakorn Nitipiromchai
///
/// CREATE DATE : 30-Apr-2019
///
/// CURRENT VERSION NO : 1.1.2
///
/// LAST RELEASE DATE  : 21-Nov-2019
///
/// MODIFICATION HISTORY :
///     1.0         30-Apr-2019     First Version
///     1.1.0       17-Sep-2019     flushes logState and not backup sync in case of self sync
///     1.1.1       19-Sep-2019     add copy mode feature to enable 1 to 1 copying (keep the same name for input and output)
///     1.1.2       21-Nov-2019     fix state file checking and able to uncompress input file then concat output
///     1.1.3       21-Nov-2019     fix external decode/unzip file logic
///     1.1.4       23-Jun-2021     add logic for retry copying and dedicated log of uncopy file
///
///

#ifndef __NFS_COPY_H__
#define __NFS_COPY_H__

#ifdef  __cplusplus
    extern "C" {
#endif

#include <ftw.h>
#include "nfs_ini_def.h"

#define _APP_NAME_              "nfs_copy"
#define _APP_VERS_              "1.1.4"

#define STATE_SUFF              ".proclist"
#define ALERT_SUFF              ".alrt"
#define MERGE_SUFF              ".mergelist"
#define RETRY_SUFF              ".copy_failed"

#define     MAX_RUNNING_SEQ     1000
#define     OUT_DATA_EXT        ".dat"
#define     OUT_SYNC_EXT        ".syn"

typedef enum {
    E_YMD8 = 0,
    E_NEID,
    E_NETTYPE,
    E_YMD14,
    E_SYN_DATSIZE,
    E_DAT_DATSIZE,
    E_LEAF_SYN,
    E_SYN_FILE,
    E_LEAF_DAT,
    E_DAT_FILE,
    NOF_VSNAP
} E_VSNAP;

typedef enum {
    E_NORMAL = 0,
    E_FIRST,
    E_NEW,
    E_VALID,
    E_SINGLE
} E_CMD_ARG;


// Main functions
int     buildSnapFile(const char *snapfile);
int     _chkSynFile(const char *fpath, const struct stat *info, int typeflag, struct FTW *ftwbuf);
int     chkSnapVsState(const char *isnap, const char *osnap);
int     chkSnapVsData(const char *isnap, const char *osnap);
int     chkSnapVsData_Self(FILE *isnap, FILE *osnap);
int     chkSnapVsData_VaryLeaf(FILE *isnap, FILE *osnap);
int     isSynStable(const char *fname, int stable_sec, char *mod_ymd, unsigned long *fsize);
int     wrtOutput(const char *snapfile);
int     relocDataAndGenSync(const char *full_catfile, const char *synfile, char snpInf[][SIZE_ITEM_L], int snpsize);
int     one2oneCopy(const char *snapfile);
void    prepLeafDir(const char *orig, char snp[][SIZE_ITEM_L], const char *yyyymmdd, char *out);
void    doBackup(char snp[][SIZE_ITEM_L]);
int     mapNetType(char *nettype, char *cdrfeedtype);
int     logState(const char *leaf_dir, const char *file_name);
int     logFail(const char *leaf_dir, const char *file_name);
int     logMergeList(const char *oper, const char *file_name);
void    clearOldState();

// Utility functions
void    getStrToken(char item[][SIZE_ITEM_L], int item_size, char *str, char *sep);
void    getItemFromStr(const char *str, char *fno, const char *sep, char *out);
int     readConfig(int argc, char *argv[]);
void    logHeader();
void    printUsage();
int     validateIni();
int     _ini_callback(const char *section, const char *key, const char *value, void *userdata);
void    makeIni();
int     chkStateAndConcat(const char *oFileName);
void    chkAlertNoSync();
int     extDecoder(const char *full_fname, char *full_decoded);
void    chkToDelete(const char *fname_del, const char *fname_ori);
void    getCksumStr(const char *fname, char *cksum_str, size_t ck_size);

#ifdef  __cplusplus
    }
#endif


#endif  // __NFS_COPY_H__
