#ifndef LICHTIEMPHONG_H
#define LICHTIEMPHONG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "DMChuNuoi.hpp"
#include "DMThuoc.hpp"
#include "PhieuKhamBenh.hpp"

using namespace std;

class LichTiemPhong {
private:
    string maChuNuoi;
    string thongTinThuCung;
    string ngayTiem;
    string loaiVacXin;
    string ghiChu;
    bool f; // Cờ đánh dấu trạng thái xóa (true: đã xóa, false: chưa xóa)

public:
    // Hàm tạo mặc định
    LichTiemPhong() : maChuNuoi(""), thongTinThuCung(""), ngayTiem(""), loaiVacXin(""), ghiChu(""), f(false) {}

    // Setter
    void setMaChuNuoi(string ma) { maChuNuoi = ma; }
    void setThongTinThuCung(string thongTin) { thongTinThuCung = thongTin; }
    void setNgayTiem(string ngay) { ngayTiem = ngay; }
    void setLoaiVacXin(string loai) { loaiVacXin = loai; }
    void setGhiChu(string ghiChu) { this->ghiChu = ghiChu; }
    void setF(bool trangThai) { f = trangThai; }

    // Getter
    string getMaChuNuoi() { return maChuNuoi; }
    string getThongTinThuCung() { return thongTinThuCung; }
    string getNgayTiem() { return ngayTiem; }
    string getLoaiVacXin() { return loaiVacXin; }
    string getGhiChu() { return ghiChu; }
    bool getF() { return f; }

    // Hàm đọc dữ liệu từ file
    static void docFile(vector<LichTiemPhong>& ds) {
        ifstream file("LichTiemPhong.txt", ios::in);
        if (!file.is_open()) {
            cout << "Khong the mo file de doc" << endl;
            return;
        }

        LichTiemPhong lich;
        string fStr;
        while (getline(file, lich.maChuNuoi)) {
            getline(file, lich.thongTinThuCung);
            getline(file, lich.ngayTiem);
            getline(file, lich.loaiVacXin);
            getline(file, lich.ghiChu);
            getline(file, fStr);
            lich.f = (fStr == "1");
            ds.push_back(lich);
        }
        file.close();
    }

    // Ghi toàn bộ danh sách vào file
    static void ghiFile(const vector<LichTiemPhong>& danhSachLich) {
        ofstream file("LichTiemPhong.txt", ios::trunc);
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi!" << endl;
            return;
        }

        for (const auto& lich : danhSachLich) {
            file << lich.maChuNuoi << "\n";
            file << lich.thongTinThuCung << "\n";
            file << lich.ngayTiem << "\n";
            file << lich.loaiVacXin << "\n";
            file << lich.ghiChu << "\n";
            file << (lich.f ? "1" : "0") << "\n";
        }
        file.close();
    }

    // Hàm kiểm tra lịch tiêm có trùng không (dựa trên mã chủ nuôi và ngày tiêm)
    static bool kiemTraTrung(vector<LichTiemPhong>& danhSachLich, const string& maChuNuoi, const string& ngayTiem) {
        for (auto& lich : danhSachLich) {
            if (lich.getMaChuNuoi() == maChuNuoi && lich.getNgayTiem() == ngayTiem && !lich.getF()) {
                return true; // Lịch đã tồn tại
            }
        }
        return false; // Lịch không trùng
    }

    // Hàm thêm lịch tiêm
    static void themLichTiem(vector<LichTiemPhong>& danhSachLich, vector<DMChuNuoi>& danhSachChuNuoi) {
        LichTiemPhong lich;
        string maChuNuoi, ngayTiem;

        // Nhập mã chủ nuôi và kiểm tra
        cout << "Nhap ma chu nuoi: ";
        getline(cin, maChuNuoi);
        bool chuNuoiTonTai = false;
        string thongTinThuCung;
        for (auto& cn : danhSachChuNuoi) {
            if (cn.getMaChuNuoi() == maChuNuoi && !cn.getF()) {
                chuNuoiTonTai = true;
                thongTinThuCung = cn.getThongTinThuCung();
                break;
            }
        }
        if (!chuNuoiTonTai) {
            cout << "Ma chu nuoi khong ton tai hoac da bi xoa!\n";
            return;
        }
        lich.setMaChuNuoi(maChuNuoi);
        lich.setThongTinThuCung(thongTinThuCung);

        // Nhập ngày tiêm và kiểm tra trùng
        cout << "Nhap ngay tiem (yyyy-mm-dd): ";
        getline(cin, ngayTiem);
        if (kiemTraTrung(danhSachLich, maChuNuoi, ngayTiem)) {
            cout << "Lich tiem voi ma chu nuoi " << maChuNuoi << " va ngay tiem " << ngayTiem << " da ton tai!\n";
            return;
        }
        lich.setNgayTiem(ngayTiem);

        // Nhập các thông tin còn lại
        string loaiVacXin, ghiChu;
        cout << "Nhap loai vac xin: ";
        getline(cin, loaiVacXin);
        cout << "Nhap ghi chu: ";
        getline(cin, ghiChu);
        lich.setLoaiVacXin(loaiVacXin);
        lich.setGhiChu(ghiChu);

        // Thêm vào danh sách
        danhSachLich.push_back(lich);

        // Ghi lại vào file
        ofstream file("LichTiemPhong.txt", ios::app);
        if (file.is_open()) {
            file << lich.getMaChuNuoi() << "\n";
            file << lich.getThongTinThuCung() << "\n";
            file << lich.getNgayTiem() << "\n";
            file << lich.getLoaiVacXin() << "\n";
            file << lich.getGhiChu() << "\n";
            file << (lich.f ? "1" : "0") << "\n";
            file.close();
            cout << "Them lich tiem thanh cong!\n";
        } else {
            cout << "Khong the mo file de ghi!\n";
        }
    }

    // Hàm sửa thông tin lịch tiêm
    static void suaLichTiem(vector<LichTiemPhong>& danhSachLich) {
        string maChuNuoi, ngayTiem;
        cout << "Nhap ma chu nuoi: ";
        getline(cin, maChuNuoi);
        cout << "Nhap ngay tiem (yyyy-mm-dd): ";
        getline(cin, ngayTiem);

        bool found = false;
        for (auto& lich : danhSachLich) {
            if (lich.getMaChuNuoi() == maChuNuoi && lich.getNgayTiem() == ngayTiem && !lich.f) {
                found = true;
                cout << "Tim thay lich tiem:\n";
                cout << "Ma Chu Nuoi: " << lich.getMaChuNuoi() << "\n";
                cout << "Thong Tin Thu Cung: " << lich.getThongTinThuCung() << "\n";
                cout << "Ngay Tiem: " << lich.getNgayTiem() << "\n";
                cout << "Loai Vac Xin: " << lich.getLoaiVacXin() << "\n";
                cout << "Ghi Chu: " << lich.getGhiChu() << "\n";

                cout << "Nhap thong tin moi (nhan Enter de giu nguyen):\n";
                string input;
                cout << "Loai vac xin (" << lich.getLoaiVacXin() << "): ";
                getline(cin, input);
                if (!input.empty()) lich.setLoaiVacXin(input);

                cout << "Ghi chu (" << lich.getGhiChu() << "): ";
                getline(cin, input);
                if (!input.empty()) lich.setGhiChu(input);

                ghiFile(danhSachLich);
                cout << "Sua thong tin lich tiem thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay lich tiem voi ma chu nuoi " << maChuNuoi << " va ngay tiem " << ngayTiem << " hoac lich da bi xoa!\n";
        }
    }

    // Hàm xóa lịch tiêm
    static void xoaLichTiem(vector<LichTiemPhong>& danhSachLich) {
        string maChuNuoi, ngayTiem;
        cout << "Nhap ma chu nuoi: ";
        getline(cin, maChuNuoi);
        cout << "Nhap ngay tiem (yyyy-mm-dd): ";
        getline(cin, ngayTiem);

        bool found = false;
        for (auto& lich : danhSachLich) {
            if (lich.getMaChuNuoi() == maChuNuoi && lich.getNgayTiem() == ngayTiem && !lich.f) {
                found = true;
                lich.setF(true);
                cout << "Da danh dau xoa lich tiem cho ma chu nuoi: " << maChuNuoi << "\n";
                ghiFile(danhSachLich);
                cout << "Xoa lich tiem thanh cong!\n";
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay lich tiem voi ma chu nuoi " << maChuNuoi << " va ngay tiem " << ngayTiem << " hoac lich da bi xoa!\n";
        }
    }

    // Hàm so sánh để sắp xếp theo ngày tiêm
    static bool sosanh(LichTiemPhong& a, LichTiemPhong& b) {
        return a.ngayTiem < b.ngayTiem;
    }

    // Hàm in danh sách lịch tiêm
    static void inDanhSachLich(vector<LichTiemPhong> ds) {
        bool coDuLieu = false;
        for (const auto& lich : ds) {
            if (!lich.f) {
                coDuLieu = true;
                break;
            }
        }
        if (!coDuLieu) {
            cout << "Danh sach lich tiem rong!" << endl;
            return;
        }

        // Sắp xếp theo ngày tiêm
        for (int i = 0; i < ds.size(); i++) {
            for (int j = i + 1; j < ds.size(); j++) {
                if (sosanh(ds[i], ds[j])) {
                    LichTiemPhong temp = ds[i];
                    ds[i] = ds[j];
                    ds[j] = temp;
                }
            }
        }

        // Độ rộng cột
        int w1 = 12;  // MaChuNuoi
        int w2 = 30;  // ThongTinThuCung
        int w3 = 12;  // NgayTiem
        int w4 = 15;  // LoaiVacXin
        int w5 = 50;  // GhiChu

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "Ma Chu Nuoi"
             << "|" << setw(w2) << "Thong Tin Thu Cung"
             << "|" << setw(w3) << "Ngay Tiem"
             << "|" << setw(w4) << "Loai Vac Xin"
             << "|" << setw(w5) << "Ghi Chu" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In dữ liệu
        for (size_t i = 0; i < ds.size(); i++) {
            if (!ds[i].f) {
                cout << "|" << right << setw(w1) << ds[i].maChuNuoi
                     << "|" << left << setw(w2) << ds[i].thongTinThuCung
                     << "|" << setw(w3) << ds[i].ngayTiem
                     << "|" << setw(w4) << ds[i].loaiVacXin
                     << "|" << setw(w5) << ds[i].ghiChu << "|" << endl;

                // In đường phân cách giữa các dòng (trừ dòng cuối)
                if (i < ds.size() - 1) {
                    bool coDongTiepTheo = false;
                    for (size_t j = i + 1; j < ds.size(); j++) {
                        if (!ds[j].f) {
                            coDongTiepTheo = true;
                            break;
                        }
                    }
                    if (coDongTiepTheo) {
                        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
                    }
                }
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
    }

    // Hàm tìm kiếm và in lịch tiêm theo mã chủ nuôi
    static void inLichCanTim(vector<LichTiemPhong> ds) {
        string maChuNuoi;
        cout << "\nNhap ma chu nuoi can tim: ";
        getline(cin, maChuNuoi);

        vector<LichTiemPhong> dsTimKiem;
        for (int i = 0; i < ds.size(); i++) {
            if (ds[i].getMaChuNuoi() == maChuNuoi && !ds[i].f) {
                dsTimKiem.push_back(ds[i]);
            }
        }

        // Độ rộng cột
        int w1 = 12;  // MaChuNuoi
        int w2 = 30;  // ThongTinThuCung
        int w3 = 12;  // NgayTiem
        int w4 = 15;  // LoaiVacXin
        int w5 = 50;  // GhiChu

        if (dsTimKiem.empty()) {
            cout << "Khong tim thay lich tiem nao cho ma chu nuoi: " << maChuNuoi << endl;
            return;
        }

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "Ma Chu Nuoi"
             << "|" << setw(w2) << "Thong Tin Thu Cung"
             << "|" << setw(w3) << "Ngay Tiem"
             << "|" << setw(w4) << "Loai Vac Xin"
             << "|" << setw(w5) << "Ghi Chu" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In dữ liệu
        for (size_t i = 0; i < dsTimKiem.size(); i++) {
            cout << "|" << left << setw(w1) << dsTimKiem[i].maChuNuoi
                 << "|" << setw(w2) << dsTimKiem[i].thongTinThuCung
                 << "|" << setw(w3) << dsTimKiem[i].ngayTiem
                 << "|" << setw(w4) << dsTimKiem[i].loaiVacXin
                 << "|" << setw(w5) << dsTimKiem[i].ghiChu << "|" << endl;

            if (i < dsTimKiem.size() - 1) {
                cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                     << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
    }

    // Hàm nhắc nhở lịch tiêm sắp tới
    static void nhacNhoLichTiem(vector<LichTiemPhong> ds) {
        string ngayHienTai;
        cout << "Nhap ngay hien tai (yyyy-mm-dd): ";
        getline(cin, ngayHienTai);

        vector<LichTiemPhong> dsNhacNho;
        for ( auto& lich : ds) {
            if (lich.getNgayTiem() >= ngayHienTai && !lich.f) {
                dsNhacNho.push_back(lich);
            }
        }

        if (dsNhacNho.empty()) {
            cout << "Khong co lich tiem nao sap den!\n";
            return;
        }

        // Sắp xếp theo ngày tiêm
        for (int i = 0; i < dsNhacNho.size(); i++) {
            for (int j = i + 1; j < dsNhacNho.size(); j++) {
                if (sosanh(dsNhacNho[i], dsNhacNho[j])) {
                    LichTiemPhong temp = dsNhacNho[i];
                    dsNhacNho[i] = dsNhacNho[j];
                    dsNhacNho[j] = temp;
                }
            }
        }

        // Độ rộng cột
        int w1 = 12;  // MaChuNuoi
        int w2 = 30;  // ThongTinThuCung
        int w3 = 12;  // NgayTiem
        int w4 = 15;  // LoaiVacXin
        int w5 = 50; // GhiChu

        // In dòng trên cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In tiêu đề cột
        cout << "|" << left << setw(w1) << "Ma Chu Nuoi"
             << "|" << setw(w2) << "Thong Tin Thu Cung"
             << "|" << setw(w3) << "Ngay Tiem"
             << "|" << setw(w4) << "Loai Vac Xin"
             << "|" << setw(w5) << "Ghi Chu" << "|" << endl;

        // In đường phân cách giữa tiêu đề và dữ liệu
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;

        // In dữ liệu
        for (size_t i = 0; i < dsNhacNho.size(); i++) {
            cout << "|" << left << setw(w1) << dsNhacNho[i].maChuNuoi
                 << "|" << setw(w2) << dsNhacNho[i].thongTinThuCung
                 << "|" << setw(w3) << dsNhacNho[i].ngayTiem
                 << "|" << setw(w4) << dsNhacNho[i].loaiVacXin
                 << "|" << setw(w5) << dsNhacNho[i].ghiChu << "|" << endl;

            if (i < dsNhacNho.size() - 1) {
                cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
                     << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
            }
        }

        // In dòng dưới cùng của bảng
        cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+" 
             << string(w3, '-') << "+" << string(w4, '-') << "+" << string(w5, '-') << "+" << endl;
    }

    // Hàm menu quản lý lịch tiêm phòng
    static void menuQuanLyLichTiemPhong(vector<LichTiemPhong>& danhSachLich, vector<DMChuNuoi>& danhSachChuNuoi) {
        int luaChon;
        do {
            cout << "\n--- QUAN LY LICH TIEM PHONG ---\n";
            cout << "1. Them lich tiem moi\n";
            cout << "2. Sua thong tin lich tiem\n";
            cout << "3. Xoa lich tiem\n";
            cout << "4. Hien thi danh sach lich tiem\n";
            cout << "5. Tim kiem lich tiem theo ma chu nuoi\n";
            cout << "6. Nhac nho lich tiem sap den\n";
            cout << "7. Quay lai\n";
            cout << "Nhap lua chon: ";
            cin >> luaChon;
            cin.ignore();

            switch (luaChon) {
                case 1:
                    cout << "=== THEM LICH TIEM ===\n";
                    themLichTiem(danhSachLich, danhSachChuNuoi);
                    break;
                case 2:
                    cout << "=== SUA THONG TIN LICH TIEM ===\n";
                    suaLichTiem(danhSachLich);
                    break;
                case 3:
                    cout << "=== XOA LICH TIEM ===\n";
                    xoaLichTiem(danhSachLich);
                    break;
                case 4:
                    cout << "=== DANH SACH LICH TIEM ===\n";
                    inDanhSachLich(danhSachLich);
                    break;
                case 5:
                    cout << "=== TIM KIEM LICH TIEM ===\n";
                    inLichCanTim(danhSachLich);
                    break;
                case 6:
                    cout << "=== NHAC NHO LICH TIEM ===\n";
                    nhacNhoLichTiem(danhSachLich);
                    break;
                case 7:
                    cout << "Quay lai menu chinh.\n";
                    return;
                default:
                    cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                    continue;
            }

            cout << "Nhan Enter de tiep tuc...";
            cin.get();
        } while (luaChon != 7);
    }
};

#endif