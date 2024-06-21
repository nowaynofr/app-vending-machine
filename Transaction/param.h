#ifndef PARAM_H
#define PARAM_H

#define DBNAME "database"
#define DBFILE "./database"
#define SQLITEMARK "SQLite format 3"
#define SQLITEMARKLEN (15)

/*
 * Common table store all config data.
 */
#define CREATE_COMMON_TABLE "create table thongtinchung(ten text UNIQUE, dulieu text)"
#define INSERT_INTO_COMMON "INSERT INTO thongtinchung (ten, dulieu) " "VALUES (:ten, :dulieu)"
#define SELECT_COMMON_ALL "SELECT * FROM thongtinchung"

#define CREATE_AUDIT_TABLE "CREATE TABLE action_audit(\
    id INTEGER PRIMARY KEY AUTOINCREMENT, \
    action_type INTEGER not null, \
    description TEXT, \
    datetime DATETIME DEFAULT CURRENT_TIMESTAMP , \
    object_type TEXT, \
    object_id TEXT, \
    object_field TEXT, \
    object_old_value TEXT, \
    object_new_value TEXT)"
#define INSERT_INTO_AUDIT "INSERT INTO action_audit"
#define CREATE_TRANSACTION_TABLE "CREATE TABLE kiosk_transaction(\
id INTEGER PRIMARY KEY AUTOINCREMENT, \
transaction_time REAL DEFAULT (datetime('now', 'localtime')), \
slot_id text,\
good_id text, \
good_name text, \
good_price integer, \
quantity integer, \
transaction_type integer, \
input_amount integer, \
order_info text, \
transaction_status integer, \
sync_status integer)"

#define CREATE_TRANSACTION "INSERT INTO kiosk_transaction ( slot_id, good_id, good_name, good_price, quantity, transaction_type, input_amount, order_info, transaction_status, sync_status) VALUES (:slot_id, :good_id, :good_name, :good_price, :quantity, :transaction_type, :input_amount, :order_info, :transaction_status, :sync_status)"
#define READ_TRANSACTION "SELECT * FROM kiosk_transaction"
#define UPDATE_TRANSACTION "UPDATE kiosk_transaction set slot_id = :slot_id, good_id = :good_id, good_name = :good_name, good_price = :good_price, quantity = :quantity, transaction_type = :transaction_type, input_amount = :input_amount, order_info = :order_info, transaction_status = :transaction_status, sync_status = :sync_status where id = :transaction_id"
#define DELETE_TRANSACTION "DELETE FROM kiosk_transaction"



#define CREATE_SALE_SESSION_TABLE "CREATE TABLE kiosk_sale_session( \
session_id INTEGER PRIMARY KEY AUTOINCREMENT, \
start_time DATETIME , \
end_time DATETIME DEFAULT CURRENT_TIMESTAMP, \
total_amount integer, \
total_bill integer, \
staff_code text, \
period text, \
period_total_amount integer, \
share_total_amount integer,\
share_period_total_amount integer,\
type text)"

#define CREATE_SALE_SESSION "INSERT INTO kiosk_sale_session ( start_time, end_time, total_amount, total_bill, staff_code, period, period_total_amount, share_total_amount, share_period_total_amount, type) VALUES (:start_time, :end_time, :total_amount, :total_bill, :staff_code, :period, :period_total_amount,:share_total_amount,:share_period_total_amount, :type)"
#define READ_ACTIVE_SALE_SESSION "SELECT * FROM kiosk_sale_session where end_time is null order by session_id desc limit 1 "
#define UPDATE_SALE_SESSION "UPDATE kiosk_sale_session set start_time = :start_time, end_time = :end_time, total_amount = :total_amount,total_bill = :total_bill, staff_code = :staff_code, period = :period, period_total_amount = :period_total_amount,share_total_amount = :share_total_amount, share_period_total_amount = :share_period_total_amount, type = :type where session_id = :session_id"
#define DELETE_SALE_SESSION "DELETE FROM kiosk_sale_session"

//V1.2 Bắt đầu
// Tạo thêm các bảng DB

#define CREATE_BILL_AMOUNT_TABLE "CREATE TABLE kiosk_bill_amount( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
sale_session_id INTEGER, \
bill_amount INTEGER, \
start_time DATETIME DEFAULT CURRENT_TIMESTAMP)"

#define CREATE_BILL_AMOUNT "INSERT INTO kiosk_bill_amount ( sale_session_id, bill_amount, start_time) VALUES ( :sale_session_id,:bill_amount, :start_time)"
#define READ_BILL_AMOUNT "SELECT * FROM kiosk_bill_amount"
#define UPDATE_BILL_AMOUNT "UPDATE kiosk_bill_amount set sale_session_id = :sale_session_id, bill_amount = :bill_amount, start_time = :start_time where id = :id"
#define DELETE_BILL_AMOUNT "DELETE FROM kiosk_bill_amount"




#define CREATE_BILL_AVAILABLE_TABLE "CREATE TABLE kiosk_bill_available( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
sale_session_id INTEGER, \
bill_available INTEGER, \
start_time DATETIME DEFAULT CURRENT_TIMESTAMP)"

#define CREATE_BILL_AVAILABLE "INSERT INTO kiosk_bill_available ( sale_session_id, bill_available, start_time) VALUES ( :sale_session_id,:bill_available, :start_time)"
#define READ_BILL_AVAILABLE "SELECT * FROM kiosk_bill_available"
#define UPDATE_BILL_AVAILABLE "UPDATE kiosk_bill_available set sale_session_id = :sale_session_id, bill_available = :bill_available, start_time = :start_time where id = :id"
#define DELETE_BILL_AVAILABLE "DELETE FROM kiosk_bill_available"



#define CREATE_BILL_STATUS_TABLE "CREATE TABLE kiosk_bill_status ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
sale_session_id INTEGER, \
bill_response INTEGER, \
bill_status text, \
start_time DATETIME DEFAULT CURRENT_TIMESTAMP)"

#define CREATE_BILL_STATUS "INSERT INTO kiosk_bill_status ( sale_session_id, bill_response, bill_status, start_time) VALUES ( :sale_session_id, :bill_response, :bill_status, :start_time)"
#define READ_BILL_STATUS "SELECT * FROM kiosk_bill_status"
#define UPDATE_BILL_STATUS "UPDATE kiosk_bill_status set sale_session_id = :sale_session_id, bill_response = :bill_response, bill_status = :bill_status, start_time = :start_time where id = :id"
#define DELETE_BILL_STATUS "DELETE FROM kiosk_bill_status"

#define CREATE_BILL_DESCRIPTION_TABLE "CREATE TABLE kiosk_Bill_StatusDescription ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
bill_response text, \
status_description text )"

#define CREATE_DESCRIPTION_STATUS "INSERT INTO kiosk_Bill_StatusDescription ( bill_response, status_description) VALUES ( :bill_response, :status_description)"
#define READ_DESCRIPTION_STATUS "SELECT * FROM kiosk_Bill_StatusDescription"
#define UPDATE_DESCRIPTION_STATUS "UPDATE kiosk_Bill_StatusDescription set bill_response = :bill_response, status_description = :status_description where id = :id"
#define DELETE_DESCRIPTION_STATUS "DELETE FROM kiosk_Bill_StatusDescription"


#define CREATE_ERROR_KIOSK_TABLE "CREATE TABLE kiosk_error ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
error_code text, \
error_code_description text, \
error_group text, \
error_level text,\
signal_count integer,\
signal_count_max integer )"

#define CREATE_ERROR_KIOSK "INSERT INTO kiosk_error ( error_code, error_code_description, error_group, error_level, signal_count,signal_count_max ) VALUES ( :error_code, :error_code_description, :error_group, :error_level, :signal_count, :signal_count_max)"
#define READ_ERROR_KIOSK "SELECT * FROM kiosk_error"
#define UPDATE_ERROR_KIOSK "UPDATE kiosk_error set bill_response = :bill_response, status_description = :status_description where id = :id"
#define DELETE_ERROR_KIOSK "DELETE FROM kiosk_error"
#define INSERT_ERROR_KIOSK_TABLE "INSERT OR IGNORE INTO kiosk_error ( error_code, error_code_description, error_group, error_level, signal_count, signal_count_max) VALUES (:error_code, :error_code_description, :error_group, :error_level, :signal_count, :signal_count_max)"
#define UPDATE_SIGNAL_COUNT "UPDATE kiosk_error set signal_count = :signal_count where error_code = :error_code"
#define UPDATE_SIGNAL_COUNT_MAX "UPDATE kiosk_error set signal_count_max = :signal_count_max where error_code = :error_code"
#define UPDATE_RESET_SIGNAL_COUNT "UPDATE kiosk_error SET signal_count = 0 WHERE id > 0"
#define DELETE_ERROR_KIOSK "DELETE FROM kiosk_error"

//V1.2 Kết thúc
#define CREATE_INVENTORY_TABLE "CREATE TABLE kiosk_inventory(\
name_service text, \
tray_id integer not null default -1, \
slot_id integer not null default -1, \
good_id text, \
good_name text, \
good_price integer, \
good_count integer, \
max_count integer )"

#define SELECT_INVENTORY "SELECT * FROM kiosk_inventory WHERE name_service = :name_service "
#define INSERT_INVENTORY "INSERT OR IGNORE INTO kiosk_inventory ( name_service, tray_id, slot_id, good_id, good_name, good_price, good_count, max_count) VALUES (:name_service, :tray_id, :slot_id, :good_id, :good_name, :good_price, :good_count, :max_count)"
#define DELETE_INVENTORY "DELETE FROM kiosk_inventory"



#define SELECT_INVENTORY_GOOD_ID "SELECT good_id from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"
#define SELECT_INVENTORY_GOOD_NAME "SELECT good_name from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"
#define SELECT_INVENTORY_GOOD_COUNT "SELECT good_count from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"
#define SELECT_INVENTORY_MAX_COUNT "SELECT max_count from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"
#define SELECT_INVENTORY_TRAY "SELECT tray_id from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"
#define SELECT_INVENTORY_SLOT "SELECT slot_id from kiosk_inventory where name_service = :name_service and good_price = :good_price limit 1"

#define CREATE_MENU_TABLE "CREATE TABLE kiosk_menu_good(\
id INTEGER PRIMARY KEY AUTOINCREMENT, \
Industry text, \
goodType text, \
serviceType text, \
good_id text, \
good_name text, \
good_price integer, \
permission text, \
charge_type_quatity integer, \
list_charge_type text, \
share_sale_permission )"

#define SELECT_GOODID_MENU_TABLE "SELECT good_id from kiosk_menu_good where goodType = :goodType and good_price = :good_price and permission = :permission limit 1"
#define SELECT_GOODID1_MENU_TABLE "SELECT good_id from kiosk_menu_good where Industry = :Industry and goodType = :goodType and permission = :permission limit 1"
#define SELECT_GOODID_COUPON_MENU_TABLE "SELECT good_id from kiosk_menu_good where serviceType = :serviceType and goodType = :goodType and permission = :permission limit 1"



#define SELECT_GOODNAME_MENU_TABLE "SELECT good_name from kiosk_menu_good where good_id = :good_id and permission = :permission limit 1"
#define SELECT_LISTCHARGETYPE_MENU_TABLE "SELECT list_charge_type from kiosk_menu_good where good_id = :good_id and permission = :permission limit 1"
#define SELECT_SHARE_SALE_PERMISSION_MENU_TABLE "SELECT share_sale_permission from kiosk_menu_good where good_id = :good_id and permission = :permission limit 1"

#define SELECT_NAMESERVICE_MENU_TABLE "SELECT serviceType from kiosk_menu_good where goodType = :goodType and good_price = :good_price and permission = :permission limit 1"
#define SELECT_NAMESERVICE1_MENU_TABLE "SELECT serviceType from kiosk_menu_good where Industry = :Industry and goodType = :goodType and permission = :permission limit 1"
#define SELECT_GOODPRICE1_MENU_TABLE "SELECT good_price from kiosk_menu_good where good_id = :good_id and permission = :permission limit 1"
#define SELECT_GOODPRICE_MENU_TABLE "SELECT good_price from kiosk_menu_good where Industry = :Industry and goodType = :goodType and permission = :permission"
#define SELECT_TYPECOUPON_MENU_TABLE "SELECT serviceType from kiosk_menu_good where Industry = :Industry and goodType = :goodType and permission = :permission"


#define INSERT_MENUGOOD_TABLE "INSERT OR IGNORE INTO kiosk_menu_good ( Industry, goodType, serviceType, good_id, good_name, good_price, permission, charge_type_quatity, list_charge_type, share_sale_permission) VALUES (:Industry, :goodType, :serviceType, :good_id, :good_name, :good_price, :permission, :charge_type_quatity,:list_charge_type,:share_sale_permission)"
#define DELETE_MENUGOOD_TABLE "DELETE FROM kiosk_menu_good"

#define CREATE_MENU_GENERAL_TABLE "CREATE TABLE kiosk_menu_good_general(\
id INTEGER PRIMARY KEY AUTOINCREMENT, \
Industry text, \
supplier text, \
good_name text, \
good_id text, \
good_price integer, \
good_quatity integer, \
image_url text, \
charge_type_quatity integer, \
list_charge_type text, \
priority integer, \
status text)"

#define SELECT_LISTCHARGETYPE_MENU_GENERAL_TABLE "SELECT list_charge_type from kiosk_menu_good_general where good_id = :good_id and status = :status limit 1"

#define INSERT_MENUGOOD_GENERAL_TABLE "INSERT OR IGNORE INTO kiosk_menu_good_general ( Industry, supplier, good_name, good_id, good_price,good_quatity,image_url, charge_type_quatity, list_charge_type, priority, status) VALUES (:Industry, :supplier, :good_name, :good_id, :good_price,:good_quatity, :image_url, :charge_type_quatity, :list_charge_type, :priority, :status)"
#define SELECT_SHARE_SALE_PERMISSION_MENU_GENERAL_TABLE "SELECT share_sale_permission from kiosk_menu_good_general where good_id = :good_id and status = :status limit 1"
#define DELETE_MENUGOOD_GENERAL_TABLE "DELETE FROM kiosk_menu_good_general"

#define CREATE_KIOSK_ADMIN_TABLE "CREATE TABLE kiosk_admin(\
id INTEGER PRIMARY KEY AUTOINCREMENT, \
category text, \
part text, \
value text )"


#define INSERT_KIOSK_ADMIN "INSERT INTO kiosk_admin ( category, part,value) VALUES (:category, :part,:value)"
#define DELETE_KIOSK_ADMIN_TABLE "DELETE FROM kiosk_admin"
#define INSERT_KIOSK_ADMIN_TABLE "INSERT OR IGNORE INTO kiosk_admin ( category, part,value) VALUES (:category, :part, :value)"


#define CONFIG_PATH "setting.ini"
#define GOOD_NAME_MAXLENGTH 50
#endif // PARAM_H

