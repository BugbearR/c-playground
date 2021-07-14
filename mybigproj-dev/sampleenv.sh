if [ ! ${MYBIGPROJ_DEV_DIR:+x} ]; then
echo MYBIGPROJ_DEV_DIR is undefined
export MYBIGPROJ_DEV_DIR=$(cd .;pwd)
fi

printf "MYBIGPROJ_DEV_DIR=%s\n" "$MYBIGPROJ_DEV_DIR"
