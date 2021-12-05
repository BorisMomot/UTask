package api

import (
	"reflect"
	"testing"
)

func TestFindComponentById(t *testing.T) {

	c1 := Component{Id: 1, Name: "C1"}
	c2 := Component{Id: 2, Name: "C2"}
	c3 := Component{Id: 3, Name: "C3"}
	clst := []Component{c1, c2, c3}

	type args struct {
		components []Component
		id         int64
	}
	tests := []struct {
		name  string
		args  args
		want  Component
		want1 bool
	}{
		{"c1 find ok", args{clst, 1}, c1, true},
		{"c2 find ok", args{clst, 3}, c3, true},
		{"not found", args{clst, 5}, Component{}, false},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, got1 := FindComponentById(tt.args.components, tt.args.id)
			if !reflect.DeepEqual(got, tt.want) {
				t.Errorf("FindComponentById() got = %v, want %v", got, tt.want)
			}
			if got1 != tt.want1 {
				t.Errorf("FindComponentById() got1 = %v, want %v", got1, tt.want1)
			}
		})
	}
}

func TestFindProjectById(t *testing.T) {
	p1 := Project{Id: 1, Name: "P1"}
	p2 := Project{Id: 2, Name: "P2"}
	p3 := Project{Id: 3, Name: "P3"}
	plst := []Project{p1, p2, p3}
	type args struct {
		projects []Project
		id       int64
	}
	tests := []struct {
		name  string
		args  args
		want  Project
		want1 bool
	}{
		{"p1 find ok", args{plst, 1}, p1, true},
		{"p2 find ok", args{plst, 3}, p3, true},
		{"not found", args{plst, 5}, Project{}, false},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, got1 := FindProjectById(tt.args.projects, tt.args.id)
			if !reflect.DeepEqual(got, tt.want) {
				t.Errorf("FindProjectById() got = %v, want %v", got, tt.want)
			}
			if got1 != tt.want1 {
				t.Errorf("FindProjectById() got1 = %v, want %v", got1, tt.want1)
			}
		})
	}
}
