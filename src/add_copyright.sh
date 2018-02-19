/**
 *  @file FILENAME
 *  @brief FILE DESCRIPTIOn
 *  @author Svätopluk Hanzel (xhanze10), FIT VUT, 2BIT, a.y. 2016/2017
 */
#!/usr/bin/env sh
shopt -s nullglob
for file in *; do
  if [ -f "$file" ]; then
    cat copyright.txt "$file" >> tempfile;
    mv tempfile "$file";
  fi
done
