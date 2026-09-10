awk '
/void Clear\(\) \{/ {
    print "\tvoid Clear() {"
    print "\t\tfor (auto& kv : object_value) {"
    print "\t\t\tdelete kv.second;"
    print "\t\t}"
    print "\t\tobject_value.clear();"
    print "\t\tarray_value.clear();"
    print "\t\tstring_value.clear();"
    print "\t}"
    in_clear = 1
    next
}
in_clear && /^	}$/ {
    in_clear = 0
    next
}
!in_clear { print }
' json.h > json.h.new
mv json.h.new json.h
