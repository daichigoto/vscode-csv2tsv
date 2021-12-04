#include <stdio.h>
#include <windows.h>

char *file2str(const char *filepath) {
  /*
   * 指定されたファイルを開く
   */
  HANDLE hFile;

  // ファイルを開く
  hFile = CreateFile(filepath, // ファイル名
    GENERIC_READ,              // 読み込みのために開く
    0,                         // 共有しない
    NULL,                      // デフォルトセキュリティ
    OPEN_EXISTING,             // 既存のファイルを開く
    FILE_ATTRIBUTE_NORMAL,     // 通常のファイル
    NULL);                     // 属性およびフラグなし

  // ファイルが開けなかった場合の処理
  if (INVALID_HANDLE_VALUE == hFile) {
    fprintf(stderr, "no such file: %s\n", filepath);
    exit(EXIT_FAILURE);
  }

  /*
   * ファイルサイズを取得し、ファイルサイズ+1のメモリを確保
   */
  DWORD dwFileSize;
  dwFileSize = GetFileSize(hFile, NULL);

  // ヒープを生成
  HANDLE hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0, 0);

  // ヒープからメモリを確保
  char *buf, *p;
  int buflen = dwFileSize + 1;
  buf = (char*)HeapAlloc(hHeap, 
    HEAP_ZERO_MEMORY, 
    sizeof(char) * buflen);
  p = buf;

  /*
   * ファイルの中身をメモリへ読み込み
   */
  DWORD dwBytesRead;
  while (ReadFile(hFile, p, buflen, &dwBytesRead, NULL) 
    && dwBytesRead > 0) {
    p += dwBytesRead;
  }

  /*
   * ファイルを閉じる
   */
  CloseHandle(hFile);

  /*
   * ヒープを閉じる
   */
  CloseHandle(hHeap);

  return buf;
}
