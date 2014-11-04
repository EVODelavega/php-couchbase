char *PCBC_PHP_CODESTR = \
"/**\n" \
" * Various constants used for flags, data-type encoding and decoding, etc...\n" \
" * throughout this SDK.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/** @internal */ define('COUCHBASE_VAL_MASK', 0x1F);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_STRING', 0);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_LONG', 1);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_DOUBLE', 2);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_BOOL', 3);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_SERIALIZED', 4);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_IGBINARY', 5);\n" \
"/** @internal */ define('COUCHBASE_VAL_IS_JSON', 6);\n" \
"/** @internal */ define('COUCHBASE_COMPRESSION_MASK', 0x7 << 5);\n" \
"/** @internal */ define('COUCHBASE_COMPRESSION_NONE', 0 << 5);\n" \
"/** @internal */ define('COUCHBASE_COMPRESSION_ZLIB', 1 << 5);\n" \
"/** @internal */ define('COUCHBASE_COMPRESSION_FASTLZ', 2 << 5);\n" \
"/** @internal */ define('COUCHBASE_COMPRESSION_MCISCOMPRESSED', 1 << 4);\n" \
"\n" \
"/** @internal */ define('COUCHBASE_SERTYPE_JSON', 0);\n" \
"/** @internal */ define('COUCHBASE_SERTYPE_IGBINARY', 1);\n" \
"/** @internal */ define('COUCHBASE_SERTYPE_PHP', 2);\n" \
"/** @internal */ define('COUCHBASE_CMPRTYPE_NONE', 0);\n" \
"/** @internal */ define('COUCHBASE_CMPRTYPE_ZLIB', 1);\n" \
"/** @internal */ define('COUCHBASE_CMPRTYPE_FASTLZ', 2);\n" \
"\n" \
"/** @internal */ define('COUCHBASE_CFFMT_MASK', 0xFF << 24);\n" \
"/** @internal */ define('COUCHBASE_CFFMT_PRIVATE', 1 << 24);\n" \
"/** @internal */ define('COUCHBASE_CFFMT_JSON', 2 << 24);\n" \
"/** @internal */ define('COUCHBASE_CFFMT_RAW', 3 << 24);\n" \
"/** @internal */ define('COUCHBASE_CFFMT_STRING', 4 << 24);\n" \
"/**\n" \
" * Various helpers for dealing with connection strings.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * Normalizes a connection string object.\n" \
" *\n" \
" * @param $dsnObj A connstr object.\n" \
" * @return array\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function _cbdsn_normalize($dsnObj) {\n" \
"    $out = array();\n" \
"\n" \
"    if (isset($dsnObj['scheme'])) {\n" \
"        $out['scheme'] = $dsnObj['scheme'];\n" \
"    } else {\n" \
"        $out['scheme'] = '';\n" \
"    }\n" \
"\n" \
"    $out['hosts'] = array();\n" \
"    if (isset($dsnObj['hosts'])) {\n" \
"        if (is_string($dsnObj['hosts'])) {\n" \
"            $dsnObj['hosts'] = array($dsnObj['hosts']);\n" \
"        }\n" \
"\n" \
"        foreach($dsnObj['hosts'] as $host) {\n" \
"            if (is_string($host)) {\n" \
"                $portPos = strstr($host, ':');\n" \
"                if ($portPos) {\n" \
"                    $hostName = substr($host, 0, $portPos);\n" \
"                    $portNum = intval(substr($host, $portPos+1));\n" \
"                    array_push($out['hosts'], array(\n" \
"                        $hostName, $portNum\n" \
"                    ));\n" \
"                } else {\n" \
"                    array_push($out['hosts'], $host);\n" \
"                }\n" \
"            } else {\n" \
"                array_push($out['hosts'], $host);\n" \
"            }\n" \
"        }\n" \
"    }\n" \
"\n" \
"    if (isset($dsnObj['bucket'])) {\n" \
"        $out['bucket'] = $dsnObj['bucket'];\n" \
"    } else {\n" \
"        $out['bucket'] = 'default';\n" \
"    }\n" \
"\n" \
"    if (isset($dsnObj['options'])) {\n" \
"        $out['options'] = $dsnObj['options'];\n" \
"    } else {\n" \
"        $out['options'] = array();\n" \
"    }\n" \
"\n" \
"    return $out;\n" \
"}\n" \
"\n" \
"/**\n" \
" * Normalizes a connection string object or string.\n" \
" *\n" \
" * @param $dsn A connection string or connstr object.\n" \
" * @return array|string\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function cbdsn_normalize($dsn) {\n" \
"    if (is_string($dsn)) {\n" \
"        return _cbdsn_stringify(\n" \
"            _cbdsn_normalize(\n" \
"                _cbdsn_parse($dsn)\n" \
"            )\n" \
"        );\n" \
"    }\n" \
"    return _cbdsn_normalize($dsn);\n" \
"}\n" \
"\n" \
"/**\n" \
" * Parses a connection string into a object.\n" \
" *\n" \
" * @param $dsn A connection string.\n" \
" * @return array\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function _cbdsn_parse($dsn) {\n" \
"    $out = array();\n" \
"\n" \
"    if (!$dsn) {\n" \
"        return $out;\n" \
"    }\n" \
"\n" \
"    preg_match(\"/((.*):\\\\/\\\\/)?([^\\\\/?]*)(\\\\/([^\\\\?]*))?(\\\\?(.*))?/\", $dsn, $parts);\n" \
"    if (isset($parts[2])) {\n" \
"        $out['scheme'] = $parts[2];\n" \
"    }\n" \
"    if (isset($parts[3])) {\n" \
"        $out['hosts'] = array();\n" \
"\n" \
"        preg_match_all(\"/([^;\\\\,\\\\:]+)(:([0-9]*))?(;\\\\,)?/\", $parts[3], $hosts, PREG_SET_ORDER);\n" \
"        foreach($hosts as $host) {\n" \
"            array_push($out['hosts'], array(\n" \
"                $host[1],\n" \
"                isset($host[3]) ? intval($host[3]) : 0\n" \
"            ));\n" \
"        }\n" \
"    }\n" \
"    if (isset($parts[5])) {\n" \
"        $out['bucket'] = $parts[5];\n" \
"    }\n" \
"    if (isset($parts[7])) {\n" \
"        $out['options'] = array();\n" \
"\n" \
"        preg_match_all(\"/([^=]*)=([^&?]*)[&?]?/\", $parts[7], $kvs, PREG_SET_ORDER);\n" \
"        foreach($kvs as $kv) {\n" \
"            $out['options'][urldecode($kv[1])] = urldecode($kv[2]);\n" \
"        }\n" \
"    }\n" \
"\n" \
"    return $out;\n" \
"}\n" \
"\n" \
"/**\n" \
" * Parses a connection string and ensures its normalized.\n" \
" *\n" \
" * @param $dsn A connection string.\n" \
" * @return array\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function cbdsn_parse($dsn) {\n" \
"    return _cbdsn_normalize(_cbdsn_parse($dsn));\n" \
"}\n" \
"\n" \
"/**\n" \
" * Converts a connstr object to a connection string.\n" \
" *\n" \
" * @param $dsnObj\n" \
" * @return string\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function _cbdsn_stringify($dsnObj) {\n" \
"    $dsn = '';\n" \
"\n" \
"    if ($dsnObj['scheme']) {\n" \
"        $dsn .= $dsnObj['scheme'] . '://';\n" \
"    }\n" \
"\n" \
"    foreach($dsnObj['hosts'] as $i => $host) {\n" \
"        if ($i !== 0) {\n" \
"            $dsn .= ',';\n" \
"        }\n" \
"        $dsn .= $host[0];\n" \
"        if ($host[1]) {\n" \
"            $dsn .= ':' . $host[1];\n" \
"        }\n" \
"    }\n" \
"\n" \
"    if ($dsnObj['bucket']) {\n" \
"        $dsn .= '/' . $dsnObj['bucket'];\n" \
"    }\n" \
"\n" \
"    if ($dsnObj['options']) {\n" \
"        $isFirstOption = true;\n" \
"        foreach($dsnObj['options'] as $k => $v) {\n" \
"            if ($isFirstOption) {\n" \
"                $dsn .= '?';\n" \
"                $isFirstOption = false;\n" \
"            } else {\n" \
"                $dsn .= '&';\n" \
"            }\n" \
"            $dsn .= urlencode($k) . '=' . urlencode($v);\n" \
"        }\n" \
"    }\n" \
"\n" \
"    return $dsn;\n" \
"}\n" \
"\n" \
"/**\n" \
" * Ensures a connstr object is normalized then generates a connection string.\n" \
" *\n" \
" * @param $dsnObj\n" \
" * @return string\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function cbdsn_stringify($dsnObj) {\n" \
"    return _cbdsn_stringify(_cbdsn_normalize($dsnObj));\n" \
"}\n" \
"/**\n" \
" * Various transcoder functions that are packaged by default with the\n" \
" * PHP SDK.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * The default options for V1 encoding when using the default\n" \
" * transcoding functionality.\n" \
" * @internal\n" \
" */\n" \
"$COUCHBASE_DEFAULT_ENCOPTS = array(\n" \
"    'sertype' => COUCHBASE_SERTYPE_JSON,\n" \
"    'cmprtype' => COUCHBASE_CMPRTYPE_NONE,\n" \
"    'cmprthresh' => 0,\n" \
"    'cmprfactor' => 0\n" \
");\n" \
"\n" \
"/**\n" \
" * The default options from past versions of the PHP SDK.\n" \
" * @internal\n" \
" */\n" \
"$COUCHBASE_OLD_ENCOPTS = array(\n" \
"    'sertype' => COUCHBASE_SERTYPE_PHP,\n" \
"    'cmprtype' => COUCHBASE_CMPRTYPE_NONE,\n" \
"    'cmprthresh' => 2000,\n" \
"    'cmprfactor' => 1.3\n" \
");\n" \
"\n" \
"/**\n" \
" * The default options for V1 decoding when using the default\n" \
" * transcoding functionality.\n" \
" * @internal\n" \
" */\n" \
"$COUCHBASE_DEFAULT_DECOPTS = array(\n" \
"    'jsonassoc' => false\n" \
");\n" \
"\n" \
"/**\n" \
" * Performs encoding of user provided types into binary form for\n" \
" * on the server according to the original PHP SDK specification.\n" \
" *\n" \
" * @internal\n" \
" *\n" \
" * @param $value The value passed by the user\n" \
" * @param $options Various encoding options\n" \
" * @return array An array specifying the bytes, flags and datatype to store\n" \
" */\n" \
"function couchbase_basic_encoder_v1($value, $options) {\n" \
"    $data = NULL;\n" \
"    $flags = 0;\n" \
"    $datatype = 0;\n" \
"\n" \
"    $sertype = $options['sertype'];\n" \
"    $cmprtype = $options['cmprtype'];\n" \
"    $cmprthresh = $options['cmprthresh'];\n" \
"    $cmprfactor = $options['cmprfactor'];\n" \
"\n" \
"    $vtype = gettype($value);\n" \
"    if ($vtype == 'string') {\n" \
"        $flags = COUCHBASE_VAL_IS_STRING | COUCHBASE_CFFMT_STRING;\n" \
"        $data = $value;\n" \
"    } else if ($vtype == 'integer') {\n" \
"        $flags = COUCHBASE_VAL_IS_LONG | COUCHBASE_CFFMT_JSON;\n" \
"        $data = (string)$value;\n" \
"        $cmprtype = COUCHBASE_CMPRTYPE_NONE;\n" \
"    } else if ($vtype == 'double') {\n" \
"        $flags = COUCHBASE_VAL_IS_DOUBLE | COUCHBASE_CFFMT_JSON;\n" \
"        $data = (string)$value;\n" \
"        $cmprtype = COUCHBASE_CMPRTYPE_NONE;\n" \
"    } else if ($vtype == 'boolean') {\n" \
"        $flags = COUCHBASE_VAL_IS_BOOL | COUCHBASE_CFFMT_JSON;\n" \
"        $data = $value ? 'true' : 'false';\n" \
"        $cmprtype = COUCHBASE_CMPRTYPE_NONE;\n" \
"    } else {\n" \
"        if ($sertype == COUCHBASE_SERTYPE_JSON) {\n" \
"            $flags = COUCHBASE_VAL_IS_JSON | COUCHBASE_CFFMT_JSON;\n" \
"            $data = json_encode($value);\n" \
"        } else if ($sertype == COUCHBASE_SERTYPE_IGBINARY) {\n" \
"            $flags = COUCHBASE_VAL_IS_IGBINARY | COUCHBASE_CFFMT_PRIVATE;\n" \
"            $data = igbinary_serialize($value);\n" \
"        } else if ($sertype == COUCHBASE_SERTYPE_PHP) {\n" \
"            $flags = COUCHBASE_VAL_IS_SERIALIZED | COUCHBASE_CFFMT_PRIVATE;\n" \
"            $data = serialize($value);\n" \
"        }\n" \
"    }\n" \
"\n" \
"    if (strlen($data) < $cmprthresh) {\n" \
"        $cmprtype = COUCHBASE_CMPRTYPE_NONE;\n" \
"    }\n" \
"\n" \
"    if ($cmprtype != COUCHBASE_CMPRTYPE_NONE) {\n" \
"        $cmprdata = NULL;\n" \
"        $cmprflags = COUCHBASE_COMPRESSION_NONE;\n" \
"\n" \
"        if ($cmprtype == COUCHBASE_CMPRTYPE_ZLIB) {\n" \
"            $cmprdata = gzencode($data);\n" \
"            $cmprflags = COUCHBASE_COMPRESSION_ZLIB;\n" \
"        } else if ($cmprtype == COUCHBASE_CMPRTYPE_FASTLZ) {\n" \
"            $cmprdata = fastlz_compress($data);\n" \
"            $cmprflags = COUCHBASE_COMPRESSION_FASTLZ;\n" \
"        }\n" \
"\n" \
"        if ($cmprdata != NULL) {\n" \
"            if (strlen($data) > strlen($cmprdata) * $cmprfactor) {\n" \
"                $data = $cmprdata;\n" \
"                $flags |= $cmprflags;\n" \
"                $flags |= COUCHBASE_COMPRESSION_MCISCOMPRESSED;\n" \
"\n" \
"                $flags &= ~COUCHBASE_CFFMT_MASK;\n" \
"                $flags |= COUCHBASE_CFFMT_PRIVATE;\n" \
"            }\n" \
"        }\n" \
"    }\n" \
"\n" \
"    return array($data, $flags, $datatype);\n" \
"}\n" \
"\n" \
"/**\n" \
" * Performs decoding of the server provided binary data into\n" \
" * PHP types according to the original PHP SDK specification.\n" \
" *\n" \
" * @internal\n" \
" *\n" \
" * @param $bytes The binary received from the server\n" \
" * @param $flags The flags received from the server\n" \
" * @param $datatype The datatype received from the server\n" \
" * @return mixed The resulting decoded value\n" \
" *\n" \
" * @throws CouchbaseException\n" \
" */\n" \
"function couchbase_basic_decoder_v1($bytes, $flags, $datatype, $options) {\n" \
"    $cffmt = $flags & COUCHBASE_CFFMT_MASK;\n" \
"    $sertype = $flags & COUCHBASE_VAL_MASK;\n" \
"    $cmprtype = $flags & COUCHBASE_COMPRESSION_MASK;\n" \
"\n" \
"    $data = $bytes;\n" \
"    if ($cffmt != 0 && $cffmt != COUCHBASE_CFFMT_PRIVATE) {\n" \
"        if ($cffmt == COUCHBASE_CFFMT_JSON) {\n" \
"            $retval = json_decode($data, $options['jsonassoc']);\n" \
"        } else if ($cffmt == COUCHBASE_CFFMT_RAW) {\n" \
"            $retval = $data;\n" \
"        } else if ($cffmt == COUCHBASE_CFFMT_STRING) {\n" \
"            $retval = (string)$data;\n" \
"        } else {\n" \
"            throw new CouchbaseException(\"Unknown flags value -- cannot decode value\");\n" \
"        }\n" \
"    } else {\n" \
"        if ($cmprtype == COUCHBASE_COMPRESSION_ZLIB) {\n" \
"            $bytes = gzdecode($bytes);\n" \
"        } else if ($cmprtype == COUCHBASE_COMPRESSION_FASTLZ) {\n" \
"            $data = fastlz_decompress($bytes);\n" \
"        }\n" \
"\n" \
"        $retval = NULL;\n" \
"        if ($sertype == COUCHBASE_VAL_IS_STRING) {\n" \
"            $retval = $data;\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_LONG) {\n" \
"            $retval = intval($data);\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_DOUBLE) {\n" \
"            $retval = floatval($data);\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_BOOL) {\n" \
"            $retval = boolval($data);\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_JSON) {\n" \
"            $retval = json_decode($data, $options['jsonassoc']);\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_IGBINARY) {\n" \
"            $retval = igbinary_unserialize($data);\n" \
"        } else if ($sertype == COUCHBASE_VAL_IS_SERIALIZED) {\n" \
"            $retval = unserialize($data);\n" \
"        }\n" \
"    }\n" \
"\n" \
"    return $retval;\n" \
"}\n" \
"\n" \
"/**\n" \
" * Default passthru encoder which simply passes data\n" \
" * as-is rather than performing any transcoding.\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function couchbase_passthru_encoder($value) {\n" \
"    return array($value, 0, 0);\n" \
"}\n" \
"\n" \
"/**\n" \
" * Default passthru encoder which simply passes data\n" \
" * as-is rather than performing any transcoding.\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function couchbase_passthru_decoder($bytes, $flags, $datatype) {\n" \
"    return $bytes;\n" \
"}\n" \
"\n" \
"/**\n" \
" * The default encoder for the client.  Currently invokes the\n" \
" * v1 encoder directly with the default set of encoding options.\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function couchbase_default_encoder($value) {\n" \
"    global $COUCHBASE_DEFAULT_ENCOPTS;\n" \
"    return couchbase_basic_encoder_v1($value, $COUCHBASE_DEFAULT_ENCOPTS);\n" \
"}\n" \
"\n" \
"/**\n" \
" * The default decoder for the client.  Currently invokes the\n" \
" * v1 decoder directly.\n" \
" *\n" \
" * @internal\n" \
" */\n" \
"function couchbase_default_decoder($bytes, $flags, $datatype) {\n" \
"    global $COUCHBASE_DEFAULT_DECOPTS;\n" \
"    return couchbase_basic_decoder_v1($bytes, $flags, $datatype, $COUCHBASE_DEFAULT_DECOPTS);\n" \
"}\n" \
"/**\n" \
" * File for the CouchbaseViewQuery class.\n" \
" */\n" \
"\n" \
"/**\n" \
" * Represents a view query to be executed against a Couchbase bucket.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class CouchbaseViewQuery {\n" \
"    /**\n" \
"     * @var string\n" \
"     * @internal\n" \
"     */\n" \
"    public $ddoc = '';\n" \
"\n" \
"    /**\n" \
"     * @var string\n" \
"     * @internal\n" \
"     */\n" \
"    public $name = '';\n" \
"\n" \
"    /**\n" \
"     * @var array\n" \
"     * @internal\n" \
"     */\n" \
"    public $options = array();\n" \
"\n" \
"    const UPDATE_BEFORE = 1;\n" \
"    const UPDATE_NONE = 2;\n" \
"    const UPDATE_AFTER = 3;\n" \
"\n" \
"    const ORDER_ASCENDING = 1;\n" \
"    const ORDER_DESCENDING = 2;\n" \
"\n" \
"    /**\n" \
"     * @internal\n" \
"     */\n" \
"    private function __construct() {\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Creates a new Couchbase ViewQuery instance for performing a view query.\n" \
"     *\n" \
"     * @param $ddoc The name of the design document to query.\n" \
"     * @param $name The name of the view to query.\n" \
"     * @return _CouchbaseDefaultViewQuery\n" \
"     */\n" \
"    static public function from($ddoc, $name) {\n" \
"        $res = new _CouchbaseDefaultViewQuery();\n" \
"        $res->ddoc = $ddoc;\n" \
"        $res->name = $name;\n" \
"        return $res;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Creates a new Couchbase ViewQuery instance for performing a spatial query.\n" \
"     *\n" \
"     * @param $ddoc The name of the design document to query.\n" \
"     * @param $name The name of the view to query.\n" \
"     * @return _CouchbaseSpatialViewQuery\n" \
"     */\n" \
"    static public function fromSpatial($ddoc, $name) {\n" \
"        $res = new _CouchbaseSpatialViewQuery();\n" \
"        $res->ddoc = $ddoc;\n" \
"        $res->name = $name;\n" \
"        return $res;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies the mode of updating to perform before and after executing\n" \
"     * this query.\n" \
"     *\n" \
"     * @param $stale\n" \
"     * @return $this\n" \
"     * @throws CouchbaseException\n" \
"     */\n" \
"    public function stale($stale) {\n" \
"        if ($stale == self::UPDATE_BEFORE) {\n" \
"            $this->options['stale'] = 'false';\n" \
"        } else if ($stale == self::UPDATE_NONE) {\n" \
"            $this->options['stale'] = 'ok';\n" \
"        } else if ($stale == self::UPDATE_AFTER) {\n" \
"            $this->options['stale'] = 'update_after';\n" \
"        } else {\n" \
"            throw new CouchbaseException('invalid option passed.');\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Skips a number of records from the beginning of the result set.\n" \
"     *\n" \
"     * @param $skip\n" \
"     * @return $this\n" \
"     */\n" \
"    public function skip($skip) {\n" \
"        $this->options['skip'] = '' . $skip;\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Limits the result set to a restricted number of results.\n" \
"     *\n" \
"     * @param $limit\n" \
"     * @return $this\n" \
"     */\n" \
"    public function limit($limit) {\n" \
"        $this->options['limit'] = '' . $limit;\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies custom options to pass to the server.  Note that these\n" \
"     * options are expected to be already encoded.\n" \
"     *\n" \
"     * @param $opts\n" \
"     * @return $this\n" \
"     */\n" \
"    public function custom($opts) {\n" \
"        foreach ($opts as $k => $v) {\n" \
"            $this->options[$k] = $v;\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Generates the view query as it will be passed to the server.\n" \
"     *\n" \
"     * @return string\n" \
"     * @internal\n" \
"     */\n" \
"    public function _toString($type) {\n" \
"        $path = '/_design/' . $this->ddoc . '/' . $type . '/' . $this->name;\n" \
"        $args = array();\n" \
"        foreach ($this->options as $option => $value) {\n" \
"            array_push($args, $option . '=' . $value);\n" \
"        }\n" \
"        $path .= '?' . implode('&', $args);\n" \
"        return $path;\n" \
"    }\n" \
"};\n" \
"\n" \
"/**\n" \
" * Represents a regular view query to perform against the server.  Note that\n" \
" * this object should never be instantiated directly, but instead through\n" \
" * the CouchbaseViewQuery::from method.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class _CouchbaseDefaultViewQuery extends CouchbaseViewQuery {\n" \
"\n" \
"    /**\n" \
"     * @internal\n" \
"     */\n" \
"    public function __construct() {\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Orders the results by key as specified.\n" \
"     *\n" \
"     * @param $order\n" \
"     * @return $this\n" \
"     * @throws CouchbaseException\n" \
"     */\n" \
"    public function order($order) {\n" \
"        if ($order == self::ORDER_ASCENDING) {\n" \
"            $this->options['descending'] = 'false';\n" \
"        } else if ($order == self::ORDER_DESCENDING) {\n" \
"            $this->options['descending'] = 'true';\n" \
"        } else {\n" \
"            throw new CouchbaseException('invalid option passed.');\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies a reduction function to apply to the index.\n" \
"     *\n" \
"     * @param $reduce\n" \
"     * @return $this\n" \
"     */\n" \
"    public function reduce($reduce) {\n" \
"        if ($reduce) {\n" \
"            $this->options['reduce'] = 'true';\n" \
"        } else {\n" \
"            $this->options['reduce'] = 'false';\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies the level of grouping to use on the results.\n" \
"     *\n" \
"     * @param $group_level\n" \
"     * @return $this\n" \
"     */\n" \
"    public function group($group_level) {\n" \
"        if ($group_level >= 0) {\n" \
"            $this->options['group'] = 'false';\n" \
"            $this->options['group_level'] = '' . $group_level;\n" \
"        } else {\n" \
"            $this->options['group'] = 'true';\n" \
"            $this->options['group_level'] = '0';\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies a specific key to return from the index.\n" \
"     *\n" \
"     * @param $key\n" \
"     * @return $this\n" \
"     */\n" \
"    public function key($key) {\n" \
"        $this->options['key'] = $key;\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies a list of keys to return from the index.\n" \
"     *\n" \
"     * @param $keys\n" \
"     * @return $this\n" \
"     */\n" \
"    public function keys($keys) {\n" \
"        $this->options['keys'] =\n" \
"            str_replace('\\\\\\\\', '\\\\', json_encode($keys));\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies a range of keys to return from the index.\n" \
"     *\n" \
"     * @param mixed $start\n" \
"     * @param mixed $end\n" \
"     * @param bool $inclusive_end\n" \
"     * @return $this\n" \
"     */\n" \
"    public function range($start = NULL, $end = NULL, $inclusive_end = false) {\n" \
"        if ($start !== NULL) {\n" \
"            $this->options['startkey'] =\n" \
"                str_replace('\\\\\\\\', '\\\\', json_encode($start));\n" \
"        } else {\n" \
"            $this->options['startkey'] = '';\n" \
"        }\n" \
"        if ($end !== NULL) {\n" \
"            $this->options['endkey'] =\n" \
"                str_replace('\\\\\\\\', '\\\\', json_encode($end));\n" \
"        } else {\n" \
"            $this->options['endkey'] = '';\n" \
"        }\n" \
"        $this->options['inclusive_end'] = $inclusive_end ? 'true' : 'false';\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies a range of document ids to return from the index.\n" \
"     *\n" \
"     * @param null $start\n" \
"     * @param null $end\n" \
"     * @return $this\n" \
"     */\n" \
"    public function id_range($start = NULL, $end = NULL) {\n" \
"        if ($start !== NULL) {\n" \
"            $this->options['startkey_docid'] =\n" \
"                str_replace('\\\\\\\\', '\\\\', json_encode($start));\n" \
"        } else {\n" \
"            $this->options['startkey_docid'] = '';\n" \
"        }\n" \
"        if ($end !== NULL) {\n" \
"            $this->options['endkey_docid'] =\n" \
"                str_replace('\\\\\\\\', '\\\\', json_encode($end));\n" \
"        } else {\n" \
"            $this->options['endkey_docid'] = '';\n" \
"        }\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Generates the view query as it will be passed to the server.\n" \
"     *\n" \
"     * @return string\n" \
"     */\n" \
"    public function toString() {\n" \
"        return $this->_toString('_view');\n" \
"    }\n" \
"};\n" \
"\n" \
"/**\n" \
" * Represents a spatial view query to perform against the server.  Note that\n" \
" * this object should never be instantiated directly, but instead through\n" \
" * the CouchbaseViewQuery::fromSpatial method.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class _CouchbaseSpatialViewQuery extends CouchbaseViewQuery {\n" \
"\n" \
"    /**\n" \
"     * @internal\n" \
"     */\n" \
"    public function __construct() {\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Specifies the bounding box to search within.\n" \
"     *\n" \
"     * @param number[] $bbox\n" \
"     * @return $this\n" \
"     */\n" \
"    public function bbox($bbox) {\n" \
"        $this->options['bbox'] = implode(',', $bbox);\n" \
"        return $this;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Generates the view query as it will be passed to the server.\n" \
"     *\n" \
"     * @return string\n" \
"     */\n" \
"    public function toString() {\n" \
"        return $this->_toString('_spatial');\n" \
"    }\n" \
"};\n" \
"/**\n" \
" * File for the CouchbaseN1qlQuery class.\n" \
" */\n" \
"\n" \
"/**\n" \
" * Represents a N1QL query to be executed against a Couchbase bucket.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class CouchbaseN1qlQuery {\n" \
"    /**\n" \
"     * @var string\n" \
"     * @internal\n" \
"     */\n" \
"    public $querystr = '';\n" \
"\n" \
"    /**\n" \
"     * Creates a new N1qlQuery instance directly from a N1QL DML.\n" \
"     * @param $str\n" \
"     * @return CouchbaseNq1lQuery\n" \
"     */\n" \
"    static public function fromString($str) {\n" \
"        $res = new CouchbaseNq1lQuery();\n" \
"        $res->querystr = $str;\n" \
"        return $res;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Generates the N1QL string as it will be passed to the server.\n" \
"     *\n" \
"     * @return string\n" \
"     */\n" \
"    public function toString() {\n" \
"        return $this->querystr;\n" \
"    }\n" \
"}\n" \
"/**\n" \
" * File for the CouchbaseCluster class.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * Represents a cluster connection.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class CouchbaseCluster {\n" \
"    /**\n" \
"     * @var _CouchbaseCluster\n" \
"     * @ignore\n" \
"     *\n" \
"     * Pointer to a manager instance if there is one.\n" \
"     */\n" \
"    private $_manager = NULL;\n" \
"\n" \
"    /**\n" \
"     * @var string\n" \
"     * @ignore\n" \
"     *\n" \
"     * A cluster DSN to connect with.\n" \
"     */\n" \
"    private $_dsn;\n" \
"\n" \
"    /**\n" \
"     * Creates a connection to a cluster.\n" \
"     *\n" \
"     * Creates a CouchbaseCluster object and begins the bootstrapping\n" \
"     * process necessary for communications with the Couchbase Server.\n" \
"     *\n" \
"     * @param string $dsn A cluster DSn to connect with.\n" \
"     * @param string $username The username for the cluster.\n" \
"     * @param string $password The password for the cluster.\n" \
"     *\n" \
"     * @throws CouchbaseException\n" \
"     */\n" \
"    public function __construct($dsn = 'http://127.0.0.1/', $username = '', $password = '') {\n" \
"        $this->_dsn = cbdsn_parse($dsn);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Constructs a connection to a bucket.\n" \
"     *\n" \
"     * @param string $name The name of the bucket to open.\n" \
"     * @param string $password The bucket password to authenticate with.\n" \
"     * @return CouchbaseBucket A bucket object.\n" \
"     *\n" \
"     * @throws CouchbaseException\n" \
"     *\n" \
"     * @see CouchbaseBucket CouchbaseBucket\n" \
"     */\n" \
"    public function openBucket($name = 'default', $password = '') {\n" \
"        $bucketDsn = cbdsn_normalize($this->_dsn);\n" \
"        $bucketDsn['bucket'] = $name;\n" \
"        $dsnStr = cbdsn_stringify($bucketDsn);\n" \
"        return new CouchbaseBucket($dsnStr, $name, $password);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Creates a manager allowing the management of a Couchbase cluster.\n" \
"     *\n" \
"     * @param $username The administration username.\n" \
"     * @param $password The administration password.\n" \
"     * @return CouchbaseClusterManager\n" \
"     */\n" \
"    public function manager($username, $password) {\n" \
"        if (!$this->_manager) {\n" \
"            $this->_manager = new CouchbaseClusterManager(\n" \
"                cbdsn_stringify($this->_dsn), $username, $password);\n" \
"        }\n" \
"        return $this->_manager;\n" \
"    }\n" \
"\n" \
"}\n" \
"/**\n" \
" * File for the CouchbaseClusterManager class.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * Class exposing the various available management operations that can be\n" \
" * performed on a cluster.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class CouchbaseClusterManager {\n" \
"    /**\n" \
"     * @var _CouchbaseCluster\n" \
"     * @ignore\n" \
"     *\n" \
"     * Pointer to our C binding backing class.\n" \
"     */\n" \
"    private $_me;\n" \
"\n" \
"    /**\n" \
"     * Constructs a cluster manager connection.\n" \
"     *\n" \
"     * @param string $connstr A connection string to connect with.\n" \
"     * @param string $username The username to authenticate with.\n" \
"     * @param string $password The password to authenticate with.\n" \
"     *\n" \
"     * @private\n" \
"     * @ignore\n" \
"     */\n" \
"    public function __construct($connstr, $username, $password) {\n" \
"        $this->_me = new _CouchbaseCluster($connstr, $username, $password);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Lists all buckets on this cluster.\n" \
"     *\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function listBuckets() {\n" \
"        $path = \"/pools/default/buckets\";\n" \
"        $res = $this->_me->http_request(2, 1, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Creates a new bucket on this cluster.\n" \
"     *\n" \
"     * @param string $name The bucket name.\n" \
"     * @param array $opts The options for this bucket.\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function createBucket($name, $opts = array()) {\n" \
"        $myOpts = array(\n" \
"            'name' => $name,\n" \
"            'authType' => 'sasl',\n" \
"            'bucketType' => 'couchbase',\n" \
"            'ramQuotaMB' => 100,\n" \
"            'replicaNumber' => 1\n" \
"        );\n" \
"        foreach($opts as $k => $v) {\n" \
"            $myOpts[$k] = $v;\n" \
"        }\n" \
"\n" \
"        $path = \"/pools/default/buckets\";\n" \
"        $args = array();\n" \
"        foreach ($opts as $option => $value) {\n" \
"            array_push($args, $option . '=' . $value);\n" \
"        }\n" \
"        $path .= '?' . implode('&', $args);\n" \
"\n" \
"        $res = $this->_me->http_request(2, 2, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Deletes a bucket from the cluster.\n" \
"     *\n" \
"     * @param string $name\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function removeBucket($name) {\n" \
"        $path = \"/pools/default/buckets/\" + $name;\n" \
"        $res = $this->_me->http_request(2, 4, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves cluster status information\n" \
"     *\n" \
"     * Returns an associative array of status information as seen\n" \
"     * on the cluster.  The exact structure of the returned data\n" \
"     * can be seen in the Couchbase Manual by looking at the\n" \
"     * cluster /info endpoint.\n" \
"     *\n" \
"     * @return mixed The status information.\n" \
"     *\n" \
"     * @throws CouchbaseException\n" \
"     */\n" \
"    public function info() {\n" \
"        $path = \"/pools/default\";\n" \
"        $res = $this->_me->http_request(2, 1, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"} \n" \
"/**\n" \
" * File for the CouchbaseBucket class.\n" \
" *\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * Represents a bucket connection.\n" \
" *\n" \
" * Note: This class must be constructed by calling the openBucket\n" \
" * method of the CouchbaseCluster class.\n" \
" *\n" \
" * @property integer $operationTimeout\n" \
" * @property integer $viewTimeout\n" \
" * @property integer $durabilityInterval\n" \
" * @property integer $durabilityTimeout\n" \
" * @property integer $httpTimeout\n" \
" * @property integer $configTimeout\n" \
" * @property integer $configDelay\n" \
" * @property integer $configNodeTimeout\n" \
" * @property integer $htconfigIdleTimeout\n" \
" *\n" \
" * @package Couchbase\n" \
" *\n" \
" * @see CouchbaseCluster::openBucket()\n" \
" */\n" \
"class CouchbaseBucket {\n" \
"    /**\n" \
"     * @var _CouchbaseBucket\n" \
"     * @ignore\n" \
"     *\n" \
"     * Pointer to our C binding backing class.\n" \
"     */\n" \
"    private $me;\n" \
"\n" \
"    /**\n" \
"     * @var string\n" \
"     * @ignore\n" \
"     *\n" \
"     * The name of the bucket this object represents.\n" \
"     */\n" \
"    private $name;\n" \
"\n" \
"    /**\n" \
"     * @var _CouchbaseCluster\n" \
"     * @ignore\n" \
"     *\n" \
"     * Pointer to a manager instance if there is one.\n" \
"     */\n" \
"    private $_manager;\n" \
"\n" \
"    /**\n" \
"     * @var array\n" \
"     * @ignore\n" \
"     *\n" \
"     * A list of N1QL nodes to query.\n" \
"     */\n" \
"    private $queryhosts = NULL;\n" \
"\n" \
"    /**\n" \
"     * Constructs a bucket connection.\n" \
"     *\n" \
"     * @private\n" \
"     * @ignore\n" \
"     *\n" \
"     * @param string $dsn A cluster DSN to connect with.\n" \
"     * @param string $name The name of the bucket to connect to.\n" \
"     * @param string $password The password to authenticate with.\n" \
"     *\n" \
"     * @private\n" \
"     */\n" \
"    public function __construct($dsn, $name, $password) {\n" \
"        $this->me = new _CouchbaseBucket($dsn, $name, $password);\n" \
"        $this->me->setTranscoder(\"couchbase_default_encoder\", \"couchbase_default_decoder\");\n" \
"        $this->name = $name;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Returns an instance of a CouchbaseBucketManager for performing management\n" \
"     * operations against a bucket.\n" \
"     *\n" \
"     * @return CouchbaseBucketManager\n" \
"     */\n" \
"    public function manager() {\n" \
"        if (!$this->_manager) {\n" \
"            $this->_manager = new CouchbaseBucketManager(\n" \
"                $this->me, $this->name);\n" \
"        }\n" \
"        return $this->_manager;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Enables N1QL support on the client.  A cbq-server URI must be passed.\n" \
"     * This method will be deprecated in the future in favor of automatic\n" \
"     * configuration through the connected cluster.\n" \
"     *\n" \
"     * @param $hosts An array of host/port combinations which are N1QL servers\n" \
"     * attached to the cluster.\n" \
"     */\n" \
"    public function enableN1ql($hosts) {\n" \
"        if (is_array($hosts)) {\n" \
"            $this->queryhosts = $hosts;\n" \
"        } else {\n" \
"            $this->queryhosts = array($hosts);\n" \
"        }\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Inserts a document.  This operation will fail if\n" \
"     * the document already exists on the cluster.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param mixed $val\n" \
"     * @param array $options expiry,flags\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function insert($ids, $val = NULL, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->insert($ids, $val, $options));\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Inserts or updates a document, depending on whether the\n" \
"     * document already exists on the cluster.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param mixed $val\n" \
"     * @param array $options expiry,flags\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function upsert($ids, $val = NULL, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->upsert($ids, $val, $options));\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Replaces a document.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param mixed $val\n" \
"     * @param array $options cas,expiry,flags\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function replace($ids, $val = NULL, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->replace($ids, $val, $options));\n" \
"    }\n" \
"    \n" \
"    /**\n" \
"     * Appends content to a document.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param mixed $val\n" \
"     * @param array $options cas\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function append($ids, $val = NULL, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->append($ids, $val, $options));\n" \
"    }\n" \
"    \n" \
"    /**\n" \
"     * Prepends content to a document.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param mixed $val\n" \
"     * @param array $options cas\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function prepend($ids, $val = NULL, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->prepend($ids, $val, $options));\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Deletes a document.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param array $options cas\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function remove($ids, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->remove($ids, $options));\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves a document.\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param array $options lock\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function get($ids, $options = array()) {\n" \
"        return $this->me->get($ids, $options);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves a document and simultaneously updates its expiry.\n" \
"     *\n" \
"     * @param string $id\n" \
"     * @param integer $expiry\n" \
"     * @param array $options\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function getAndTouch($id, $expiry, $options = array()) {\n" \
"        $options['expiry'] = $expiry;\n" \
"        return $this->me->getAndTouch($id, $expiry, $options);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves a document and locks it.\n" \
"     *\n" \
"     * @param string $id\n" \
"     * @param array $options\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function getAndLock($id, $options = array()) {\n" \
"        return $this->me->get($id, $options);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves a document from a replica.\n" \
"     *\n" \
"     * @param string $id\n" \
"     * @param array $options\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function getFromReplica($id, $options = array()) {\n" \
"        return $this->me->getFromReplica($id, $options);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Increment or decrements a key (based on $delta).\n" \
"     *\n" \
"     * @param string|array $ids\n" \
"     * @param integer $delta\n" \
"     * @param array $options initial,expiry\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function counter($ids, $delta, $options = array()) {\n" \
"        return $this->_endure($ids, $options,\n" \
"            $this->me->counter($ids, $delta, $options));\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Unlocks a key previous locked with a call to get().\n" \
"     * @param string|array $ids\n" \
"     * @param array $options cas\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function unlock($ids, $options = array()) {\n" \
"        return $this->me->unlock($ids, $options);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Executes a view query.\n" \
"     *\n" \
"     * @param ViewQuery $queryObj\n" \
"     * @return mixed\n" \
"     * @throws CouchbaseException\n" \
"     *\n" \
"     * @internal\n" \
"     */\n" \
"    public function _view($queryObj) {\n" \
"        $path = $queryObj->toString();\n" \
"        $res = $this->me->http_request(1, 1, $path, NULL, 1);\n" \
"        $out = json_decode($res, true);\n" \
"        if (isset($out['error'])) {\n" \
"            throw new CouchbaseException($out['error'] . ': ' . $out['reason']);\n" \
"        }\n" \
"        return $out;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Performs a N1QL query.\n" \
"     *\n" \
"     * @param $dmlstring\n" \
"     * @return mixed\n" \
"     * @throws CouchbaseException\n" \
"     *\n" \
"     * @internal\n" \
"     */\n" \
"    public function _query($dmlstring) {\n" \
"        if ($this->queryhosts == NULL) {\n" \
"            throw new CouchbaseException('no available query nodes');\n" \
"        }\n" \
"\n" \
"        $hostidx = array_rand($this->queryhosts, 1);\n" \
"        $host = $this->queryhosts[$hostidx];\n" \
"\n" \
"        $ch = curl_init();\n" \
"        curl_setopt($ch, CURLOPT_URL, 'http://' . $host . '/query');\n" \
"        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);\n" \
"        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'POST');\n" \
"        curl_setopt($ch, CURLOPT_POSTFIELDS, $dmlstring);\n" \
"        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);\n" \
"        curl_setopt($ch, CURLOPT_HTTPHEADER, array(\n" \
"                'Content-Type: text/plain',\n" \
"                'Content-Length: ' . strlen($dmlstring))\n" \
"        );\n" \
"        $result = curl_exec($ch);\n" \
"        curl_close($ch);\n" \
"\n" \
"        $resjson = json_decode($result, true);\n" \
"\n" \
"        if (isset($resjson['error'])) {\n" \
"            throw new CouchbaseException($resjson['error']['cause'], 999);\n" \
"        }\n" \
"\n" \
"        return $resjson['resultset'];\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Performs a query (either ViewQuery or N1qlQuery).\n" \
"     *\n" \
"     * @param CouchbaseQuery $query\n" \
"     * @return mixed\n" \
"     * @throws CouchbaseException\n" \
"     */\n" \
"    public function query($query) {\n" \
"        if ($query instanceof _CouchbaseDefaultViewQuery ||\n" \
"            $query instanceof _CouchbaseSpatialViewQuery) {\n" \
"            return $this->_view($query);\n" \
"        } else if ($query instanceof CouchbaseN1qlQuery) {\n" \
"            return $this->_query($query->querystr);\n" \
"        } else {\n" \
"            throw new CouchbaseException(\n" \
"                'Passed object must be of type ViewQuery or N1qlQuery');\n" \
"        }\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Flushes a bucket (clears all data).\n" \
"     *\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function flush() {\n" \
"        return $this->me->flush();\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Sets custom encoder and decoder functions for handling serialization.\n" \
"     *\n" \
"     * @param string $encoder The encoder function name\n" \
"     * @param string $decoder The decoder function name\n" \
"     */\n" \
"    public function setTranscoder($encoder, $decoder) {\n" \
"        return $this->me->setTranscoder($encoder, $decoder);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Ensures durability requirements are met for an executed\n" \
"     *  operation.  Note that this function will automatically\n" \
"     *  determine the result types and check for any failures.\n" \
"     *\n" \
"     * @private\n" \
"     * @ignore\n" \
"     *\n" \
"     * @param $id\n" \
"     * @param $res\n" \
"     * @param $options\n" \
"     * @return mixed\n" \
"     * @throws Exception\n" \
"     */\n" \
"    private function _endure($id, $options, $res) {\n" \
"        if ((!isset($options['persist_to']) || !$options['persist_to']) &&\n" \
"            (!isset($options['replicate_to']) || !$options['replicate_to'])) {\n" \
"            return $res;\n" \
"        }\n" \
"        if (is_array($res)) {\n" \
"            // Build list of keys to check\n" \
"            $chks = array();\n" \
"            foreach ($res as $key => $result) {\n" \
"                if (!$result->error) {\n" \
"                    $chks[$key] = array(\n" \
"                        'cas' => $result->cas\n" \
"                    );\n" \
"                }\n" \
"            }\n" \
"\n" \
"            // Do the checks\n" \
"            $dres = $this->me->durability($chks, array(\n" \
"                'persist_to' => $options['persist_to'],\n" \
"                'replicate_to' => $options['replicate_to']\n" \
"            ));\n" \
"\n" \
"            // Copy over the durability errors\n" \
"            foreach ($dres as $key => $result) {\n" \
"                if (!$result) {\n" \
"                    $res[$key]->error = $result->error;\n" \
"                }\n" \
"            }\n" \
"\n" \
"            return $res;\n" \
"        } else {\n" \
"            if ($res->error) {\n" \
"                return $res;\n" \
"            }\n" \
"\n" \
"            $dres = $this->me->durability(array(\n" \
"                $id => array('cas' => $res->cas)\n" \
"            ), array(\n" \
"                'persist_to' => $options['persist_to'],\n" \
"                'replicate_to' => $options['replicate_to']\n" \
"            ));\n" \
"\n" \
"            if ($dres) {\n" \
"                return $res;\n" \
"            } else {\n" \
"                throw new Exception('durability requirements failed');\n" \
"            }\n" \
"        }\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Magic function to handle the retrieval of various properties.\n" \
"     *\n" \
"     * @internal\n" \
"     */\n" \
"    public function __get($name) {\n" \
"        if ($name == 'operationTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_OP_TIMEOUT);\n" \
"        } else if ($name == 'viewTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_VIEW_TIMEOUT);\n" \
"        } else if ($name == 'durabilityInterval') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_DURABILITY_INTERVAL);\n" \
"        } else if ($name == 'durabilityTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_DURABILITY_TIMEOUT);\n" \
"        } else if ($name == 'httpTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_HTTP_TIMEOUT);\n" \
"        } else if ($name == 'configTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_CONFIGURATION_TIMEOUT);\n" \
"        } else if ($name == 'configDelay') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_CONFDELAY_THRESH);\n" \
"        } else if ($name == 'configNodeTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_CONFIG_NODE_TIMEOUT);\n" \
"        } else if ($name == 'htconfigIdleTimeout') {\n" \
"            return $this->me->getOption(COUCHBASE_CNTL_HTCONFIG_IDLE_TIMEOUT);\n" \
"        }\n" \
"\n" \
"        $trace = debug_backtrace();\n" \
"        trigger_error(\n" \
"            'Undefined property via __get(): ' . $name .\n" \
"            ' in ' . $trace[0]['file'] .\n" \
"            ' on line ' . $trace[0]['line'],\n" \
"            E_USER_NOTICE);\n" \
"        return null;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Magic function to handle the setting of various properties.\n" \
"     *\n" \
"     * @internal\n" \
"     */\n" \
"    public function __set($name, $value) {\n" \
"        if ($name == 'operationTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_OP_TIMEOUT, $value);\n" \
"        } else if ($name == 'viewTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_VIEW_TIMEOUT, $value);\n" \
"        } else if ($name == 'durabilityInterval') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_DURABILITY_INTERVAL, $value);\n" \
"        } else if ($name == 'durabilityTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_DURABILITY_TIMEOUT, $value);\n" \
"        } else if ($name == 'httpTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_HTTP_TIMEOUT, $value);\n" \
"        } else if ($name == 'configTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_CONFIGURATION_TIMEOUT, $value);\n" \
"        } else if ($name == 'configDelay') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_CONFDELAY_THRESH, $value);\n" \
"        } else if ($name == 'configNodeTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_CONFIG_NODE_TIMEOUT, $value);\n" \
"        } else if ($name == 'htconfigIdleTimeout') {\n" \
"            return $this->me->setOption(COUCHBASE_CNTL_HTCONFIG_IDLE_TIMEOUT, $value);\n" \
"        }\n" \
"\n" \
"        $trace = debug_backtrace();\n" \
"        trigger_error(\n" \
"            'Undefined property via __set(): ' . $name .\n" \
"            ' in ' . $trace[0]['file'] .\n" \
"            ' on line ' . $trace[0]['line'],\n" \
"            E_USER_NOTICE);\n" \
"        return null;\n" \
"    }\n" \
"}\n" \
"/**\n" \
" * File for the CouchbaseBucketManager class.\n" \
" * @author Brett Lawson <brett19@gmail.com>\n" \
" */\n" \
"\n" \
"/**\n" \
" * Class exposing the various available management operations that can be\n" \
" * performed on a bucket.\n" \
" *\n" \
" * @package Couchbase\n" \
" */\n" \
"class CouchbaseBucketManager {\n" \
"    /**\n" \
"     * @var _CouchbaseBucket\n" \
"     * @ignore\n" \
"     *\n" \
"     * Pointer to our C binding backing class.\n" \
"     */\n" \
"    private $_me;\n" \
"\n" \
"    /**\n" \
"     * @var string\n" \
"     * @ignore\n" \
"     *\n" \
"     * Name of the bucket we are managing\n" \
"     */\n" \
"    private $_name;\n" \
"\n" \
"    /**\n" \
"     * @private\n" \
"     * @ignore\n" \
"     *\n" \
"     * @param $binding\n" \
"     * @param $name\n" \
"     */\n" \
"    public function __construct($binding, $name) {\n" \
"        $this->_me = $binding;\n" \
"        $this->_name = $name;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Returns all the design documents for this bucket.\n" \
"     *\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function getDesignDocuments() {\n" \
"        $path = \"/pools/default/buckets/\" . $this->_name . '/ddocs';\n" \
"        $res = $this->_me->http_request(2, 1, $path, NULL, 2);\n" \
"        $ddocs = array();\n" \
"        $data = json_decode($res, true);\n" \
"        foreach ($data['rows'] as $row) {\n" \
"            $name = substr($row['meta']['id'], 8);\n" \
"            $ddocs[$name] = $row['json'];\n" \
"        }\n" \
"        return $ddocs;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Inserts a design document to this bucket.  Failing if a design\n" \
"     * document with the same name already exists.\n" \
"     *\n" \
"     * @param $name Name of the design document.\n" \
"     * @param $data The design document data.\n" \
"     * @throws CouchbaseException\n" \
"     * @returns true\n" \
"     */\n" \
"    public function insertDesignDocument($name, $data) {\n" \
"        if ($this->getDesignDocument($name)) {\n" \
"            throw new CouchbaseException('design document already exists');\n" \
"        }\n" \
"        return $this->upsertDesignDocument($name, $data);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Inserts a design document to this bucket.  Overwriting any existing\n" \
"     * design document with the same name.\n" \
"     *\n" \
"     * @param $name Name of the design document.\n" \
"     * @param $data The design document data.\n" \
"     * @returns true\n" \
"     */\n" \
"    public function upsertDesignDocument($name, $data) {\n" \
"        $path = '_design/' . $name;\n" \
"        $res = $this->_me->http_request(1, 3, $path, json_encode($data), 2);\n" \
"        return true;\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves a design documents from the bucket.\n" \
"     *\n" \
"     * @param $name Name of the design document.\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function getDesignDocument($name) {\n" \
"        $path = '_design/' . $name;\n" \
"        $res = $this->_me->http_request(1, 1, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Deletes a design document from the bucket.\n" \
"     *\n" \
"     * @param $name Name of the design document.\n" \
"     * @return mixed\n" \
"     */\n" \
"    public function removeDesignDocument($name) {\n" \
"        $path = '_design/' . $name;\n" \
"        $res = $this->_me->http_request(1, 4, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"\n" \
"    /**\n" \
"     * Retrieves bucket status information\n" \
"     *\n" \
"     * Returns an associative array of status information as seen\n" \
"     * by the cluster for this bucket.  The exact structure of the\n" \
"     * returned data can be seen in the Couchbase Manual by looking\n" \
"     * at the bucket /info endpoint.\n" \
"     *\n" \
"     * @return mixed The status information.\n" \
"     */\n" \
"    public function info()\n" \
"    {\n" \
"        $path = \"/pools/default/buckets/\" . $this->name;\n" \
"        $res = $this->_me->http_request(2, 1, $path, NULL, 2);\n" \
"        return json_decode($res, true);\n" \
"    }\n" \
"} \n" \
"";
