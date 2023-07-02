#include "emscripten.h"
#include <string.h>

#include <plist/plist.h>

EMSCRIPTEN_KEEPALIVE
int to_json(char *plist, size_t plist_len, char *output, size_t output_len) {

  plist_t plist_obj = NULL;
  plist_err_t err;

  err = plist_from_memory(plist, plist_len, &plist_obj, NULL);
  if (err != PLIST_ERR_SUCCESS)
    return err;

  char *json = NULL;
  uint32_t json_len = 0;
  err = plist_to_json(plist_obj, &json, &json_len, 0);
  if (err != PLIST_ERR_SUCCESS)
    return err;

  if (json_len > output_len)
    return PLIST_ERR_INVALID_ARG;

  memcpy(output, json, json_len);

  plist_mem_free(json);
  plist_free(plist_obj);

  return PLIST_ERR_SUCCESS;
}

EMSCRIPTEN_KEEPALIVE int to_plist(char *json, size_t json_len, char *output,
                                  size_t output_len) {
  plist_t plist_obj = NULL;
  plist_err_t err;

  printf("%s\n", json);

  err = plist_from_json(json, json_len, &plist_obj);
  if (err != PLIST_ERR_SUCCESS)
    return err;

  char *plist = NULL;
  uint32_t plist_len = 0;
  err = plist_to_bin(plist_obj, &plist, &plist_len);
  if (err != PLIST_ERR_SUCCESS)
    return err;

  if (plist_len > output_len)
    return PLIST_ERR_INVALID_ARG;

  memcpy(output, plist, plist_len);

  plist_mem_free(plist);
  plist_free(plist_obj);

  return PLIST_ERR_SUCCESS;
}
