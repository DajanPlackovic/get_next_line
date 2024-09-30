make() {
    # if there is multiple arguments, treat the first as the
    # output file name, and the rest as input files
    if [ "$#" -gt 1 ]; then
        local BASENAME=$(echo $1 | sed 's/\.h$//')
        local FILENAME=$1
        shift
    # if there is only one, treat it as the input file and
    # output to the file of the same name with the .h extension
    else
        local BASENAME=$(echo $1 | sed 's/\.c$//')
        local FILENAME=$BASENAME".h"
    fi

    # make names for the definition at the top
    local DEFNAME=$(echo $BASENAME | tr '[:lower:]' '[:upper:]')
    local NDEF=$(echo "#ifndef "$DEFNAME"_H")
    local DEF=$(echo "# define "$DEFNAME"_H")

    # if the file is already there, delete everything except
    # for the header
    if [ -f $FILENAME ]; then
        awk '/\/\*.*/' $FILENAME > placeholder
        cat placeholder > $FILENAME
        echo "" >> $FILENAME
    fi

    # write everything to the header file
    echo $NDEF >> $FILENAME
    echo $DEF >> $FILENAME
    # get all the includes, remove duplicated and write them to the file
    gawk 'match($0, /#include (.*)/, a) { print "# include " a[1] }' $@ | awk '!x[$0]++' >> $FILENAME
    echo "" >> $FILENAME
    # get all the prototypes and write them into the file
    awk '/.*(int|char|void|size_t)\t.*\(.*\)/ { print $0 ";" }' $@ >> $FILENAME
    awk '!/static .*/' $FILENAME > placeholder
    cat placeholder > $FILENAME
    echo "#endif" >> $FILENAME
    rm placeholder
}

make $@
