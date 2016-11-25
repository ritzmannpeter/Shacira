#
# EB_ERR
#
ERR-I-01 Function not implemented
ERR-I-02 Invalid format for error code
ERR-E-01 General error$1{, $1}$2{, $2}
ERR-E-02 Invalid pointer$1{: $1}
ERR-E-03 Invalid handle$1{: $1}
ERR-E-04 Invalid parameter$1{ $1}$2{: $2}
ERR-E-05 Initialization error
ERR-E-06 Timeout error$1{ at $1}
ERR-E-07 Internal overflow$1{ in module $1}
ERR-E-08 Internal underflow$1{ in module $1}
ERR-F-01 Out of memory
ERR-F-02 Out of handle space

#
# EB_MSG
#
MSG-E-01 Could not open $1 for sending
MSG-E-02 Could not create $1 for receiving
MSG-E-03 Error while sending to $1
MSG-E-04 Error while receiving from $1
MSG-E-05 Tried to send an empty message to $1
MSG-E-06 Received invalid message from $1
MSG-E-07 Invalid protocol in $1
MSG-E-08 Protocol in $1 not supported
MSG-E-09 Message too long for $1
MSG-E-10 Anonymous adress not valid here

#
# EB_FILE
#
FIL-I-01 errEOF$1{: $1}
FIL-I-02 errNoMatch$1{: $1}
FIL-E-01 errIllSpec$1{: $1}
FIL-E-02 errIllDevice$1{: $1}
FIL-E-03 errIllParam$1{: $1}
FIL-E-04 errIllAccess$1{: $1}
FIL-E-05 errFileNotFound$1{: $1}
FIL-E-06 errPathNotFound$1{: $1}
FIL-E-07 errExists$1{: $1}
FIL-E-08 errPermDenied$1{: $1}
FIL-E-09 errGeneralIO$1{: $1}
FIL-E-10 errDeviceFull$1{: $1}
FIL-E-11 errWriteProt$1{: $1}
FIL-E-12 errSeek$1{: $1}
FIL-E-13 errUnget$1{: $1}
FIL-E-14 errShare$1{: $1}
FIL-E-15 errDeviceInUse$1{: $1}
FIL-E-16 errDeviceLocked$1{: $1}
FIL-E-17 errPipeBusy$1{: $1}
FIL-E-18 errDeviceNotReady$1{: $1}
FIL-E-19 errSorry$1{: $1}
FIL-F-01 errIllHandle$1{: $1}
FIL-F-02 errTableOverflow$1{: $1}
FIL-F-03 errTooManyFiles$1{: $1}
FIL-F-04 errLib$1{: $1}

#
# EDB_DATABASE
#
DBI-E-01 General database error$1{, $1}$2{, $2}
DBI-E-02 Database type not supported$1{, $1}$2{, $2}
DBI-E-03 Error during LOGIN to database$1{, $1}$2{, $2}
DBI-E-04 Timeout while accessing a database resource$1{, $1}$2{, $2}
#
DBI-E-06 Error while trying to open a record table$1{, $1}$2{, $2}
DBI-E-07 Record not ready$1{, $1}$2{, $2}
DBI-E-08 Record has changed since last access$1{, $1}$2{, $2}
#
DBI-E-11 Could not allocate a database environment$1{, $1}$2{, $2}
DBI-E-12 Could not allocate a database connection$1{, $1}$2{, $2}
DBI-E-13 Could not allocate a database cursor$1{, $1}$2{, $2}
#
DBI-E-21 Error while defining a result column$1{, $1}$2{, $2}
DBI-E-22 Error while binding a parameter value$1{, $1}$2{, $2}
DBI-E-23 One or more parameter values not bound$1{, $1}$2{, $2}
DBI-E-24 Error while binding a static parameter value$1{, $1}$2{, $2}
DBI-E-25 Error while setting the database access mode$1{, $1}$2{, $2}
DBI-E-26 Error while analyzing a SQL command$1{, $1}$2{, $2}
DBI-E-27 Error while executing a SQL command$1{, $1}$2{, $2}
DBI-E-28 Error while reading from the database$1{, $1}$2{, $2}
#
DBI-E-31 No data found$1{, $1}$2{, $2}
#
DBI-E-41 errDuplicateKey
DBI-E-42 errBindType
DBI-E-43 errFetchOutOfSeq
DBI-E-44 errVarNotInList
DBI-E-45 errColumnNull
DBI-E-46 errColumnTooLarge
DBI-E-47 errNullFetched
DBI-E-48 errColumnTrunc
DBI-E-49 errColumnUpdNull
DBI-E-50 errRowidInvalid
DBI-E-51 errValueTooLarge
DBI-E-52 errRowidUnavail
DBI-E-53 errRowidUnavail2
DBI-E-54 errRealOverflow
DBI-E-55 errCheckConstraint
DBI-E-56 errNoParentRecord
DBI-E-57 errChildRecords
DBI-E-58 errNoTrunc
DBI-E-59 errNoRetcValue
DBI-E-60 errAutoCommitFailed

#
# FBSON
#
FON-E-01 Header not found$1{: $1}
FON-E-02 Unexpected EOF$1{: $1}
FON-E-03 Illegal part$1{: $1}
FON-E-04 Template expected (File $1 line $2)
FON-E-05 Multiple template$1 (File $1 line $2)
FON-E-06 Unknown option$1{: $1}

FON-F-01 Unknown exception
FON-F-02 Display $1 not available$2{ ($2)}
FON-F-03 Machine $1 not available$2{ ($2)}

#
# CSERIAL
#
SER-F-01 Open failed$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-02 Bad Parameters$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-03 Read Data$1{: $1}$2{: $2}$3{: $3}$4{: $4}
SER-F-04 Write Data$1{: $1}$2{: $2}$3{: $3}$4{: $4}

TST-E-01 Testfehlermeldung #1
TST-E-02 Testfehlermeldung #2 <$1{xx$1}>

